#define BASESTAT 15
int wiz_fix_damage(object caster,object victim,int damage,string type)
{
   damage = (damage * (int)caster->query_int())/BASESTAT;
   damage = (damage * (100-(int)victim->query_property(type)))/100;
   return damage;
}
int cleric_fix_damage(object caster,object victim,int damage,string type)
{
   int align;
   if((string)caster->query_guild_name() == "paladin")
   {
       align = (int)victim->query_align();
       /* harm good */
       if((damage < 0) && (align < 0)) return 0;
       /* heal evil */
       if((damage > 0) && (align > 0)) return 0;
   }
   if((string)caster->query_guild_name() == "anti-paladin")
   {
       align = (int)victim->query_align();
       /* harm evil */
       if((damage < 0) && (align > 0)) return 0;
       /* heal good */
       if((damage > 0) && (align < 0)) return 0;
   }
   damage = (damage * (int)caster->query_wis())/BASESTAT;
   damage = (damage * (100-(int)victim->query_property(type)))/100;
   return damage;
}
mixed find_unique_match(string find,mixed in)
{
mixed *olist;
   int i,j;
   olist = find_match(find,in);
   for(i = 0; i < sizeof(olist); i++)
   {
      for(j = sizeof(olist)-1; j > i; j--)
      {
         if(olist[j] == olist[i]) olist = delete(olist,j,1);
      }
   }
   return olist;
}
mixed find_one_match(string find,mixed in)
{
mixed *olist;
   int i,j;
   olist = find_match(find,in);
   if(sizeof(olist)> 1)
   {
      olist = delete(olist,1,sizeof(olist)-1);
   }
   return olist;
}


/* Checks if ob is the correct alignment for doing whatever they're doing */
int wrong_alignment(object ob)
{
  switch( (string)ob->query_guild_name() )
  {
    case "paladin":
      if ( (int)ob->query_align() > 0 )
        return 1;
      break;
    case "anti-paladin":
      if ( (int)ob->query_align() < 0 )
        return 1;
      break;
    default:
      break;
  }
  
  return 0;
}

/* For (good)naughty (anti-)paladins who try to use their abilities */
int punish_align(object ob)
{
  tell_object(ob, "Thou dost feel disgracefully impure, and feel a loss "+
    "of thy confidence.\n");
  ob->set_xp(0);
  return 1;
}
