MUDB!��0#��03 global/virtual/virtual.h global/virtual/compiler.h  global/virtual/compiler.c<                P      �) |) �����  �  �
  DF��<  ����        � �      &   c��	
cj  8 T	
cj   !"#$%&'()*+,- ;8T./0123456789:;<=>?@A 	
cj  ;8T.B0123CD6789EF@A 	
cj  ;8TGHIJKLMNOPQRCD45STUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~������������������P 	
cj  ;8T(6(5 8T(���cj�^���cj�^���cj�^���cj�^���cj�^(5e7T5 5�5 ^(5 �;82;�;7	T5	�	 5	�^5 �m7T5h>5�n7T5	�5	��5 �7T5  �5 ;�;V" ��5 ;�;V	 (�5;�m7T5 �V" ��V	 (	�  5
79T	7T$ 55
�W7T579T*
 �579T55h,) 5�n7T5& �m7T5hB�7T5hB�7
T7Te 5@5
579T5@	;5
��V 57
9T55
�) 5@	;5
7T" 55
�) 5	�5@	;5
;�;�55hB,m 5	�5;�;�5	�5 ;5 � �;�;�7T� 55
�579T55
5
\ 55
5
�! 5	�55
5
;�;55

;�;�. 5	�	55
5

;�;55
5

;�;55

;�;� �55
;�;V" 55h,� 5	�cj;�;�;�	 5	�^ 7S �5 ;�;5;�;V" 5	� 5	�^5	�6((5 h	>7T 55 

) 55 
 )
 55 

) 55,)  7055 

) 55 
 )
 55 

) 55.* 555 ((5 & 7 T5 
#� >	5 h>5 7 T5 �m�c]%(	5 h>5 7 T5 ��V �;(5 �W7T5($"   �-   0    9   {   �5 ((5 �m�c]%(5 6�5& (5 6 �5& (5 6�5& (5 6�5& (5 6�5& (   `P  �    DP  Z      ��          <W  �     XW  �     X I C    �3  �    <X  �    �Y 	 �     tW  O     �W  \     �W  i     �W  v     �W  �     4  \  � p" �� @� �� 4� �� H� X� �� P �  h� t  � �� �  � D� �   �2 t� 4+ �3 <9 x� T| �� ��  t7 @ ` �O �3  �9 0 (9 � �# t# 0� �5 x2 �O �8 8� �4 �F �P �P hF $6 \E �9 D.  P �4 �P �P Q P8 �E �2 0Q LQ p4 lQ �$ �Q t5 �
 �J N `= �2 �K < �Q �Q �Q 4N �Q R (R DR `R |R �R �R �R �R S  S 8S TS hS �S �S �S �S �S T ,T DT XT tT �T �T �8 �T �7 �T  9 �T �K U U 0U LU dU �U �U �U �U �U  V x� V 0V DV X( \V |V �V �V �V �V �V W  W � lC tW �W �5 �W �� �W �6 �W 5 �W �� T� �� �� �| �( TX �X �X H7 �� |J �X h| �� X2 �} �X 0n Y �6 �' $Y �' h8 8Y LY <6 d6 �X L pY h2 �N (( �Y �Y 8} �Y �} 02 �Y Z (Z DZ `Z h9  
  5    �   �6   .   �4   �4   �    ��
 �����   global/virtual/compiler.c global/virtual/virtual.h global/virtual/compiler.h item add_item name set_name long set_long light	 set_light alias	 add_alias plural
 add_plural	 adjective add_adjective main_plural set_main_plural main plural weight
 set_weight value	 set_value property add_property clone do_clone money adjust_money short	 set_short exit add_exit modify exit modify_exit reset add_reset_item	 dark mess set_dark_mess co ord
 set_co_ord zone set_zone sign add_sign setup setup_armor	 condition set_condition enchant set_enchant ac add_ac max condition set_max_cond immune
 add_immune type set_type wear remove set_wear_remove_func	 dex minus set_dex_minus damage chance set_damage_chance
 new_weapon attack
 add_attack weapon skill set_weapon_skill
 move after set_move_after	 move zone add_move_zone race set_race class	 set_class guild	 set_guild level	 set_level skill add_skill_level equip
 init_equip	 remove ac	 remove_ac remove attack remove_attack attack everyone set_attack_everyone random stats set_random_stats
 give_money chat add_chat_string chat chance set_chat_chance achat add_achat_string achat chance set_achat_chance talk string add_talk_string join fights set_join_fights	 alignment set_al follow speed set_follow_speed	 aggresive set_aggresive str set_str con set_con dex set_dex wis set_wis	 bonus int set_bonus_int	 bonus str set_bonus_str	 bonus con set_bonus_con	 bonus dex set_bonus_dex	 bonus wis set_bonus_wis int set_int gender
 set_gender command add_known_command consentrate set_concentrate protect
 do_protect follow	 do_follow	 throw out set_throw_out /global/virtual/server r	 compile_r
 add_method ob
 compile_ob arm compile_arm wep compile_wep mon compile_mon move - .c dest_me /� #include "virtual.h"

void dest_me() { destruct(this_object()); }

void create() {
object clone;

  seteuid((string)"/secure/master"->creator_file(this_object()));
 prop_to_fun() : file   not found
 VO_COMPILER $
 
#& prop_to_fun() : Nothing but comments?
 %s
%s   
 ::   Class include
 #include < >
1   clone = (object)SERVER->create_virtual_object(" ", 1);
'   clone->add_property("virtual name", " #1 ");
   call_other(clone, " ",  );
   call_other( ,  Error: Unknown index    " "->' set_return_ob(clone);
} /* create() */
 bing Error loading  ,
 str_to_var %d // /std/room.c /std/object.c /obj/armor.c /obj/weapon.c /obj/monster.c o_funcs r_funcs	 arm_funcs	 wep_funcs	 mon_funcs	 return_ob tmp_file_no initialize_methods strip_string create query_return_ob set_return_ob extract_arguments do_clone prop_to_fun
 str_to_var	 compile_r
 compile_ob compile_arm compile_wep compile_mon,,       X  �  j k Gl km sn ko �p s t w x y z { � � � � � � � � � � � � � � � � � � � � � � � 
� 
� � � � � � � � � � � � � � � � � � � � 	� � � � � � � � � � � � � � � � .� ,� 
� 	

"#'+/  