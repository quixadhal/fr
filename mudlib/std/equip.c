/* Item.c 
 * Made by Baldrick.
 * to be used instead of /std/object on *EVERY* object that can be carried.
 * 
 * Right now it's only armour.c and weapon.c that inherits it.
 * and for now that's the only one needing it..
 * unless you have any wear / wieldable items.. the should also inherit this
 */


status wearable;
status holdable;
status in_use;
int size, armour_type;
int hands;  /* Hamlet */

mapping mylist = (["fire":1,"cold":1,"magical":1,"electrical":1,"stone":1,
  "poison":1,"air":1,"noguild":1,"nocast":1,
  "con":2,"dex":2,"str":2,"cha":2,"wis":2,"int":2
]);


void set_holdable(int i) 
{ 
    holdable = i; 
    if (wearable && holdable)
	wearable = 0;
}

void set_wearable(int i) 
{ 
    wearable = i; 
    if (wearable && holdable)
	holdable = 0;
}
/* This stuff just cleans up the code, tidies 6 repeated tests into 1
   Note that the way this is coded, it is unwise to wear "enchanted"
   items for too long, you'll take a temp hit on removal if you do
*/   	
static void stat_adjust(string query_tmp,string query_total,string adj,int j)
{
    int total,temp;
    if(!intp(j)) return;
    if(j < 0) // if removing a stat, be sure we don't kill them :)
    {
	total = call_other(ETO,query_total);
	if((total + j) < 1)
	{
	    j = 1-total;	
	}
	call_other(ETO,adj,j);
    }
    else // Otherwise don't add to it if it already exists
    {
	temp = call_other(ETO,query_tmp);
	if(temp <= 0)
	    call_other(ETO,adj,j);				
    }
}

// Major hack, Taniwha 1996
// To clean up adding reistances on magic stuff, stat mods etc
int local_in_use(int i);
int set_in_use(int i)
{
    in_use = i;
// Taniwha, see if there is any cute stuff
   if( !(sizeof(map_prop) || sizeof(timed_prop) || sizeof(query_static_properties()))) return i;
   in_use = local_in_use( i);
   return in_use;
}
int local_in_use(int i)
{
    string *ks;	   	
    string str;
    int k;
    mixed j;

    if(!ETO) return 0;
    // Taniwha 1996, guild only check.
    str = query_property("guild");
    if(stringp(str) && str != ETO->query_guild_name()) 
    {
	notify_fail("The "+query_cap_name()+" requires specialized guild skills to use.\n");
	return 0;
    }
    str = query_property("race");
    if(stringp(str) && str != ETO->query_race())
    {
	notify_fail("The "+query_cap_name()+" is made for someone with a different body shape from yours. "
	  "You just can't use it.\n");
	return 0;		 
    }
    str = query_property("sig");
    if(stringp(str) && str != ETO->query_group_name())
    {
	notify_fail("The sigils of the "+str+" flare to life on the "+query_cap_name()+
	  " preventing you from using it.\n");
	return 0;		 

    }
    str = query_property("clan");
    if(stringp(str) && str != ETO->query_race_group_name())
    {
	notify_fail("You can't bring yourself to use a "+query_cap_name()+
	  "belonging to "+str+".\n");    
    } 
    str = query_property("property");
    if(stringp(str) && ! ETO->query_property(str)) 
    {
	notify_fail("The Gods prevent you using an item you havn't earned.\n");
	return 0;
    }
    if(timed_prop && sizeof(ks = keys(timed_prop)) && ETO )
    {	
	if(i) // being worn
	{
	    str = query_property("messon");
	    if(stringp(str)) tell_object(ETO,str);
	    for(k = 0; k < sizeof(ks); k++)
	    {
		j = query_timed_property(ks[k]); // So it'll wear off
		if(mylist[ks[k]] )
		    switch(ks[k])
		{
		case "con":
		case "str":
		case "dex":
		case "wis":
		case "int":
		case "cha":
		    if(intp(j))	
			stat_adjust("query_tmp_"+ks[k],"query_"+ks[k],"adjust_tmp_"+ks[k],j);	
		    break;
		default:
		    ETO->add_static_property(ks[k],j);
		    break;   	
		}
	    }	
	}					   	      
	else // being unworn
	{
	    str = query_property("messoff");
	    if(stringp(str)) tell_object(ETO,str);
	    for(k = 0; k < sizeof(ks); k++)
	    {
		j = query_timed_property(ks[k]); // So it'll wear off
		if(mylist[ks[k]])
		    switch(ks[k])
		{
		case "con":
		case "str":
		case "dex":
		case "wis":
		case "int":
		case "cha":
		    if(intp(j))
			stat_adjust("query_tmp_"+ks[k],"query_"+ks[k],"adjust_tmp_"+ks[k],-j);
		    break;
		default:
		    ETO->remove_static_property(ks[k]);
		    break;   	
		}
	    }					   	      
	}
    }	   	
    return in_use;
}

void set_armour_type(int i)
{
    armour_type = i;
}

int query_holdable() { return holdable; }
int query_wearable() { return wearable; }
int query_in_use() { return in_use; }
int query_armour_type() { return armour_type; }

void create()
{
    holdable = wearable = 0;
    size = 0;                 // Fix by Wonderflug
    hands = 1;
}

// Move hack so that wearables/holdables will leave the wear/hold
// arrays of living creatures.
int move(mixed dest, mixed messout, mixed messin) 
{
    object ob;
    int i;
    int UNUSED_IT = 0;  /* Hamlet's nastiness */

    /* Next line is Hamlet's and it's ugly, but needed */
    if(this_object()->query_in_use()) 
    {
	this_object()->set_in_use(0);
	UNUSED_IT = 1;
    }

    ob = environment(this_object());
    i = (int)object::move(dest, messout, messin);

    if (!i && UNUSED_IT && objectp(ob) && living(ob))
    {
	if (this_object()->query_holdable())  /* Hamlet fixed me */
	    ob->unhold_ob(this_object());
	else if (this_object()->query_wearable()) /* hamlet fixed me */
	    ob->unwear_ob(this_object());
    }	
    if(i && UNUSED_IT)  this_object()->set_in_use(1); /* Hamlet */
    return i;
}

/* Sizes.. This will be used in wield and wear and later also by containers.
 * Will have it here and not in /std/object because the roomsize is something 
 * else.. 
 * Baldrick aug '95.
 */

void set_size(int i)
{
    size = i;
} /* void size */

int adjust_size(int i)
{
    size += i;
    return size;
} /* adjust_size */

int query_size()
{
    return size;
} 

/* Hamlet Sep 1995 */
void set_hands_needed(int i) 
{
    hands = i;
}

int query_hands_needed() { return hands; }

/* Added april '95 by Baldrick, does the same as the move, just for dest_me
 * Not sure if it will work tho 
 */
void dest_me()
{
    object ob;
    int i;

    ob = environment(this_object());

    if (in_use && objectp(ob) && living(ob))
	//       if (holdable)
	if (this_object()->query_holdable()) /* Hamlet fixed me */
	    ob->unhold_ob(this_object());
	//       else if (wearable)
	else if (this_object()->query_wearable()) /* Hamlet */
	    ob->unwear_ob(this_object());
    ::dest_me();
} /* void dest_me */

// Radix, needed for long()
string cond_string() { return(0); }

// Radix moved long() from /obj/weapon.c & armour.c to here.
// Also added calc_extra_look() cause it was unused (though inherited)
// Jan 18, 1996
string long(string s, int dark)
{
    string cond = cond_string();
    string xtra = calc_extra_look();
    if(!cond) cond = "";
    if(!xtra) xtra = "";
    return ::long()+xtra+cond;
}
