/*** temp shadow for Spirit Armour spell ***/

object my_player;

void setshadow(object ob) 
{
   shadow(ob,1);
   my_player = ob;
}

void destruct_shadow()
{
  destruct(this_object());
}

      
int query_spirit_armour_spell() { return 1; }

/*** query_armour_spell <- identifies which spell, if its say a shield 
 spell, it would be query_shield_spell(), etc. ***/

