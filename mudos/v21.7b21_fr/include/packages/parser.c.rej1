***************
*** 674,679 ****
      parse_info_t *pi = ob->pinfo;
      hash_entry_t *he;
  
      DEBUG_PP(("add_to_hash_table: %s", ob->name));
      for (i = 0; i < pi->num_ids; i++) {
  	he = add_hash_entry(pi->ids[i]);
--- 674,682 ----
      parse_info_t *pi = ob->pinfo;
      hash_entry_t *he;
  
+     if (!pi) /* woops.  Dested during parse_command_users() or something
+ 	        similarly nasty. */
+ 	return;
      DEBUG_PP(("add_to_hash_table: %s", ob->name));
      for (i = 0; i < pi->num_ids; i++) {
  	he = add_hash_entry(pi->ids[i]);
***************
*** 759,765 ****
  	    if (ret->u.arr->item[i].type != T_OBJECT) continue;
  	    /* check if we got them already */
  	    ob = ret->u.arr->item[i].u.ob;
! 	    env = ob->super;
  	    while (env) {
  		if (env == parse_user->super)
  		    break;
--- 762,770 ----
  	    if (ret->u.arr->item[i].type != T_OBJECT) continue;
  	    /* check if we got them already */
  	    ob = ret->u.arr->item[i].u.ob;
! 	    if (!(ob->pinfo))
! 		continue;
! 	    env = ob;
  	    while (env) {
  		if (env == parse_user->super)
  		    break;
