MUDB!��0#��0 std/races/light_defs.inc  std/races/standard.c�  �             P      ��
 ��
 ����8  �  �  �  �  ����        �� B     5 8T58T	((6(6(5 6s7T5-/ 5	;6
� 705 589T55	;89T55;89T(5 55 8<((&( &H  (	
 	 	 	 	 		 
    P P �  
  !"#$ %&'()  *	 !*	 "*	 #*	 $*	 %*	 &*	 '*	 (*	 )*	 
  + + , ,  - ./,  0 1/,  2 03.245678 23129:;<= =>2	 :>2	 ;>2	 <>2	 9>2	 8>0	 5>0	 6>0	 7>0	 4>0	 � 8T'    ?&_ (5 @) (	(	((A((	(	(5 6>, 	(5 6, (5 6;, (5 6(;. (5 6;. (5 6. ((((6(5 6s7T5,   (5	;6
� 7056
5	;6
5;6
 ((  7T7T* 56
5 ) 5	;6
5 ) 56
 7<7<56h,/ 5((d(' �  (   ��  a       ,�     %  @�     %  t�     %  d�     %  \�     %  Ч     %  |�     %  ��     %  ��    	 %  ��    
 %  �     %  D�     %  
 �
     %  h�     % 
 �
     %  
 
     %    ��     %    ��     %    ��     %   ��     %   �     %   4�     %    X� I    %   H�     %    ��  a   D   �     %   ��     %  ��     %    ��      !    X� I    e    ��  a   D    �� D     %   H�    ! %   ��    " %   �    # %   0�    $ %   ��    % %    X� I    e   ��    ' %   4�    ( %   ��    ) %    L�    * %    d�    + %    |�    , %   T|    - %   �    . %   ��    / %    ��    0 %    d� 	   1 %  |� 	   2 %   p�    3 %    ��    4 %   ��    5 %    ��    6 %   H�    7 %   �� @  8 %    �� C   9 %  X�    : %    x�    ; %  ��    < %   �� 	   = %    ��    > %    |�    ? %    ��    @ %    ��    A %     �    B %   �    C %   H�    D %    p� I   E %    X� I    e    ��    G %    t�    H %    ��    I %    ��    J %    ��    K %    ��    L %    ��    M %   D�    N %  ��     O !    ��    P %    � 	  Q %    X� I    e    ��  a   D  ��    T %   (�    U %   D�    V %    \�    W %  x� @  X %   ��    Y %    �� I   Z %  ��    [ %        \ %          ] %  \� @  ^ %   @�    _ %    <�    ` %    ��    a %    ��  a   D   ��    c %   ��    d %  �     e %    P� C   f %   �    g %   �    h %   p     i %  �     j %  �     k %       l %    $ C   m %   @    n %   X    o %  t    p %  �     q %    � C   r %    �� C   s %    tK C   t %    �K C   u %   `~    v %   |~    w %   �    x %    X� I    e   ��    z %    �    { %    �    | %   8�    } %    �    ~ %         %    p=    � %    L�    � %        � %    < 	   � %   x    � %   �    � %    �    � %   �    � %             @         �       �        `  �      �  �      ��  �     �  �     �       �              $       <  Y      T I [    l I ^    �   �      �  �       `� �   � �= �=  h| 0 H ` x � � � � � �� $� �  ��   8 P h | � � �   � �    ( @ ` � � � � �  < T h | � � L� � � �   8 T p � � � �     �� @ � L] L�   (�    ��  ,� "4� �	 � D * � -�   � 5 (� I8@�  X� M �� V0�  ��  d 8� �
g �  	�  l �� 
oX� C ,� Ct  � Cw��   � � � 	�� I  ^     �     �   std/object.c std/races/standard.c std/races/light_defs.incG The standard boring race.  Get a new one soon, this one is pretty sad.
 head   left ear	 right ear left eye	 right eye nose scalp tongue teeth skull ear eye cranium left arm arm	 left hand	 right arm
 right hand torso chest heart liver left kidney right kidney	 left lung
 right lung spleen hand
 left pinky left third finger left index finger left ring finger
 left thumb right pinky right third finger right index finger right ring finger right thumb finger kidney lung genitals left leg leg	 left foot	 right leg
 right foot foot left big toe left second toe left third toe left fourth toe left little toe right big toe right second toe right third toe right fourth toe right little toe toe unknown creature ring A small non descript person.
 map_prop
 timed_prop static_map_prop timeleft extra_looks labels short_d plural_d long_d	 read_mess max_size cur_size light	 int_light	 move_flag prev weight value name alias
 adjectives plurals	 create_me min_light_limit max_light_limit bits create query_hb_counter query_hb_diff add_property add_static_property add_timed_property remove_property remove_static_property remove_timed_property query_old_property query_static_property query_timed_property query_time_remaining traverse_timed_properties query_property_exists query_static_property_exists query_timed_property_exists query_properties query_static_properties query_timed_properties add_properties add_static_properties add_timed_properties query_init_data query_property create calc_extra_look add_extra_look remove_extra_look query_extra_look_list query_init_data create query_labels
 add_weight test_remove test_add	 add_label remove_label query_init_data	 set_short set_long set_main_plural query_short
 query_long query_main_plural short pretty_short long query_plural pretty_plural add_read_mess set_max_size query_max_size set_cur_size query_cur_size add_read_this set_read_mess query_read_mess remove_read_mess init create_read_array do_read query_light query_my_light query_int_light
 set_opaque reset_opaque adjust_light	 set_light stats query_init_data
 query_prev	 reset_get set_get
 reset_drop set_drop drop get set_move_flag move dest_me dwep query_init_data create exp adjust_weight
 set_weight query_weight adjust_money adjust_value query_money_array query_money	 set_value query_value print_object set_name
 query_name query_cap_name create set_aliases	 add_alias remove_alias query_alias id full_id set_plurals
 add_plural remove_plural add_plurals query_plurals	 id_plural set_adjectives add_adjective remove_adjective query_adjectives parse_command_id_list parse_command_plural_id_list parse_command_adjectiv_id_list query_parse_id query_frac_parse_id	 attack_by query_init_data
 set_cursed query_cursed query_enchant set_enchant query_weapon query_armour int_query_static_auto_load query_dynamic_auto_load init_static_arg query_static_auto_load init_dynamic_arg init_arg query_alive clean_up set_light_limits query_light_limith query_light_limitl add_bit query_number_type query_number_wielded query_limbs
 query_desc query_skill_bonus player_start player_quit
 query_dark	 set_level
 query_bits	 query_bit query_possible_bits query_max_level #global_init#ZZ   .  �  9 : ; ? C 	T U V W 
X Y Z \ ] a c e e f 	g h i j k l m n o p q r s s t u u v w x x y z { | } ~  � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � d � 	� � � � � � � � � � � � � � � � � � 	� � � � �  #   