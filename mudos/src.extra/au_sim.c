/*
 * The new stuff for add_action and the like :)
 */

/*
 * Find the sentence for a command from the player.
 * Return success status.
 */
int user_parser(buff)
    char *buff;
{
    struct sentence *s;
    char *p;
    int length;
    struct object *save_current_object = current_object,
                  *save_command_giver = command_giver;
    char verb_copy[SMALL_STRING_SIZE];

    if (d_flag > 1)
	debug_message("cmd [%s]: %s\n", command_giver->name, buff);
    /* strip trailing spaces. */
    for (p = buff + strlen(buff) - 1; p >= buff; p--) {
	if (*p != ' ')
	    break;
	*p = '\0';
    }
    if (buff[0] == '\0')
	return 0;
    /* strip leading spaces */
    if (*buff == ' ') {
        register i;

        for (p = buff+1; *p == ' '; p++) ;
        length = strlen(buff) + p - buff;
        for (i=0; i <= length; i++) buff[i] = p[i];
    }
    if (special_parse(buff))
	return 1;
    p = strchr(buff, ' ');
    if (p == 0)
	length = strlen(buff);
    else
	length = p - buff;
    clear_notify();
    for (s=command_giver->sent; s; s = s->next) {
	struct svalue *ret;
	int len;
	struct object *command_object;
	
	if (s->verb == 0)
	    error("An 'action' did something, but returned 0 or \
had an undefined verb.\n");
	len = strlen(s->verb);
        if (s->star != -1) { /* had a star in the verb */
          if (s->star == len) { /* star at end ie: no_space */
            if (strncmp(s->verb, buff, len) != 0) continue;
          } else { /* all up to space must match */
            if ((length > len) || (length < s->star)) continue;
            if (strncmp(buff, s->verb, length) != 0) continue;
          }
        } else {
          if (len != length) continue;
          if (strncmp(s->verb, buff, length)) continue;
        }
	/*
	 * Now we have found a special sentence !
	 */
	if (d_flag > 1)
	    debug_message("Local command %s on %s\n",
                           s->function, s->ob->name);
	if (len >= sizeof verb_copy) {
          strncpy(verb_copy, s->verb, sizeof verb_copy - 1);
          verb_copy[sizeof verb_copy] = '\0';
        } else
 	  strcpy(verb_copy, s->verb); /* the verb that was matched */
	last_verb = verb_copy;
	/*
	 * If the function is static and not defined by current object,
	 * then it will fail. If this is called directly from player input,
	 * then we set current_object so that static functions are allowed.
	 * current_object is reset just after the call to apply().
	 */
	if (current_object == 0)
	    current_object = s->ob;
	/*
	 * Remember the object, to update score.
	 */
	command_object = s->ob;
	if (s->star == len) { /* star at end */
	    push_constant_string(&buff[strlen(s->verb)]);
	    ret = apply(s->function,s->ob, 1);
	} else if (buff[length] == ' ') {
	    push_constant_string(&buff[length+1]);
	    ret = apply(s->function, s->ob, 1);
	} else {
	    ret = apply(s->function, s->ob, 0);
	}
	if (current_object->flags & O_DESTRUCTED) {
	    /* If disable_commands() were called, then there is no
	     * command_giver any longer.
	     */
	    if (command_giver == 0)
		return 1;
	    s = command_giver->sent;	/* Restart :-( */
	}
	current_object = save_current_object;
	last_verb = 0;
	/* If we get fail from the call, it was wrong second argument. */
        if (ret && ret->type == T_NUMBER && ret->u.number == 0)
          continue;
        if (!command_giver) {
          return 1;
        }
        if (s && command_giver->interactive &&
	    !(command_giver->flags & O_IS_WIZARD))
          add_moves (&command_object->stats, 1);
        if (ret == 0)
          add_message("Error: action %s not found.\n", s->function);
	return 1;
    }
    notify_no_command();
    return 0;
}

/*
 * Associate a command with function in this object.
 *
 * The first argument is the function to be called.
 *
 * The second argument is the verb to be matched.
 *
 * The optional third argument is the verbs priority.
 *
 * The object must be near the command giver, so that we ensure that the
 * sentence is removed when the command giver leaves.
 *
 * If the call is from a shadow, make it look like it is really from
 * the shadowed object.
 */
void add_action(str, cmd, priority)
    char *str, *cmd;
    int priority;
{
    struct sentence *new;
    struct sentence **prev;
    struct object *ob;
    char *pos;

    if (str[0] == ':')
	error("Illegal function name: %s\n", str);
    if (current_object->flags & O_DESTRUCTED)
	return;
    ob = current_object;
    while(ob->shadowing)
	ob = ob->shadowing;
    if (command_giver == 0 || (command_giver->flags & O_DESTRUCTED))
	return;
    if (ob != command_giver && ob->super != command_giver &&
	ob->super != command_giver->super && ob != command_giver->super)
      error("add_action from object that was not present.\n");
    if (d_flag > 1)
	debug_message("--Add action %s\n", str);
#ifdef COMPAT_MODE
    if (strcmp(str, "exit") == 0)
	error("Illegal to define a command to the exit() function.\n");
#endif
    new = alloc_sentence();
    new->function = make_shared_string(str);
    if ((pos = strchr(cmd, '*'))) { /* assumes 1 star only */
      new->star = pos - cmd;
      strcpy(pos, pos+1); /* eat star -- this portable?? */
      new->verb = make_shared_string(cmd);
      bcopy(pos, pos+1, strlen(pos)); /* the zero is already there */
      *pos = '*';
    } else {
      new->star = -1;
      new->verb = make_shared_string(cmd);
    }
    new->ob = ob;
    new->priority = priority;
    if (!command_giver->sent) {
      command_giver->sent = new;
      new->next = 0;
      return;
    }
    prev = &(command_giver->sent);
    while ((*prev) && (*prev)->priority > priority) prev = &((*prev)->next);
    new->next = *prev;
    *prev = new;
}

/*
 * Remove all commands (sentences) defined by object 'ob' in object
 * 'player'
 */
void remove_sent(ob, player)
    struct object *ob, *player;
{
    struct sentence **s;

    for (s= &player->sent; *s;) {
	struct sentence *tmp;
	if ((*s)->ob == ob) {
	    if (d_flag > 1)
		debug_message("--Unlinking sentence %s\n", (*s)->function);
	    tmp = *s;
	    *s = tmp->next;
	    free_sentence(tmp);
	} else
	    s = &((*s)->next);
    }
}

char debug_parse_buff[50]; /* Used for debugging */

/*
 * Hard coded commands, that will be available to all players. They can not
 * be redefined, so the command name should be something obscure, not likely
 * to be used in the game.
 */
int special_parse(buff)
    char *buff;
{
    if (strcmp(buff, "e") == 0) {
	(void)strcpy(buff, "east");
	return 0;
    }
    if (strcmp(buff, "w") == 0) {
	(void)strcpy(buff, "west");
	return 0;
    }
    if (strcmp(buff, "s") == 0) {
	(void)strcpy(buff, "south");
	return 0;
    }
    if (strcmp(buff, "n") == 0) {
	(void)strcpy(buff, "north");
	return 0;
    }
    if (strcmp(buff, "d") == 0) {
	(void)strcpy(buff, "down");
	return 0;
    }
    if (strcmp(buff, "u") == 0) {
	(void)strcpy(buff, "up");
	return 0;
    }
    if (strcmp(buff, "nw") == 0) {
	(void)strcpy(buff, "northwest");
	return 0;
    }
    if (strcmp(buff, "ne") == 0) {
	(void)strcpy(buff, "northeast");
	return 0;
    }
    if (strcmp(buff, "sw") == 0) {
	(void)strcpy(buff, "southwest");
	return 0;
    }
    if (strcmp(buff, "se") == 0) {
	(void)strcpy(buff, "southeast");
	return 0;
    }
    return 0;
}
