MUDB!��0#��0D include/drinks.h include/inet.h include/standard.h include/player.h  global/communicate.c  �1             P      (   ����0	  �
  �  ���  ����        � �      vv	v
vvvvvvvvvvvvv vd!^ "vd#^	 $v v(5 8T(6(5 8 T(6 (6 5 ;7T5- 58 T6 6. 68 T	(((5 8 <(5 h	>7T 7055 
 ) 55 
#�*%(&(5 5( '($!   	?   (5 h	>7T 7055 
 ) 55 
#�\hX(()(*($!   R?   U(5 h	>7T 7055 
 ) 55 
#���+(,(*($!   �?   �(c� (-5 d.^5 h>c/5^�(5  *7 T5 *) 5 0) 1V (236^ 6l4;V (5 & 7Tc5^ 5 &  7 Tk 6c7^0;5;8;5 6]69*
 :6;7<;5;<;5 & d=^	((5  *7 T5 *) 5 0) >V (236^ 6l4;V (5 & 7Tc5^ 5 &  7 Tk 6c7^0;5;?;5 6c@^]5! 69*
 :6;7<;5;A;5 & d=^	((5 F 5 *) 5F BV (5  5 CW7T7T* DV ( 5 7T236^ 6l4;V (2E6^ 6lF;G;V (5f 5�7TcH5^7T5V 7T5 5V 7T5: c!^ 5IW7T7T) J50;5;^	(5lK;V (5d) LV (5NM^ 5�F 57^O;V (& , PV (5*& 7T5** 05;Q;7Tc5^ 5 &  7 T5)*J 5Scc7^R;5;A;56^69*
 :6;7<5 T57^;5;A;5& > 5Scc7^U;56^69*
 :6;7<5 V57^;A;5& d=^	((6W) dNX^F YV (5  *7 Tw7T5 *) 5 0) ZV (& , PV (d=^c7^0;5 ;[;7T5V 5V" 	((5 F 5 *) \V (c]^ ^V (236^ 6l4;V (2E6^ 6lF;G;V (5 h
B	;@& , PV (5 &	 7T5(* _5;7T
 5`;7Tc5^ 5 &  7 T�ac7^0;5;A;5 6c@^]5(*$ 69*
 :6;7<b5;A;5 & ! 69*
 :6;7<;5;A;5 & 05 �;7 T	((cV 5  (236^ 6l4;V (5 dW7 T5 0m7T  7T7T 550nk V 7Sh  55h," 5	;d50n7T5h	)	 5
d)# d7^e;df^;g;V hV" 	(5d >7T7T 55
z 574	V 7T55h, 5h iV (c5^ 5&  7Tj7<5&
 7Tk kc7^l;5;556]m5;n;5V# ;A;5& d=^	((op5 ^	(5 `qrsQtuvwxyz V (2{5 ^ (5  8<(5 6s7S) (65	V 8T5 6)% 6h
 |8T	 6
8Tc}6;~;V (5 ! 6;�;6| ;V# ;~;V (5 6| ;s) �5 ;~;V (5 8T�5 ;�;V" 	((6(6(h  �:  �      �:         �=  �       �=  �      �=  �        >  �      >  �     
 l�
  �     D> @�     �>  ,    �>  j     (?  �    X;  �     ;  e    X<      �;  �    �<  �    �<  �      =  �     �C      4D  2     �<  |      �D  �      E C �   �1  / @/ h' �/  ; 4; H; X; p; �; �; �; �; �; �; �; < ,< D< X< l< �< �< �< �< �< �< =  = 8= H= `= � t= h� �= `> t> �~ �> �> h| �> ? <? �~ T? �} ��
 � l? ��
 � �? �� �? t� �? T1 �? �? ��
 @ @ 4@ �
 @� 8�
 D@ d�
 h@ H} �@ �@ �@ tQ �@ H� �@ ��
 A A 0A PA hA �A �A �A ��
 �A �A B ā ��
 (B �� <B XB ,�
 pB �B �B �B `�
  + t	 �B �B  C C ,C HC \C lC |C �C �C �C �C �C �C �C D PD �+ �� dD �D �D �D 4+ `:   �/    |:  D �: K�: C  �:  T �	 �     5 2 �       � F   global/communicate.c include/drinks.h include/inet.h include/standard.h include/player.h do_say sa*y '* do_loud_say lsay "* do_emote :* em*ote do_echo ec*ho do_emote_all emoteall
 do_echo_to echoto do_tell t*ell do_shout sh*out shout!
 do_whisper whi*sper set_language sp*eak do_channels 000
 eme*rgency guild query_creator cre
 query_lord demi exclaim ask say yell  asking  	 urgently  questioningly  %s%-=*s

 query_cols
 fix_string   Syntax: lsay <something>
 /obj/handlers/languages query_language_spoken  is not a spoken language.
 query_volume
 person_say query_cap_name
 s loudly:  common  in  You 	  loudly:  adjust_time_left Syntax: say <something>
 s: 	 query_int :  Syntax: tell person <message>
 %s %s Syntax: tell <name> something
 query_language_distance  is not able to spoken at a 
 distance.
 expand_nickname %s@%s /net/daemon/out_tell  is not logged in.
* Talking to yourself again.  I don't know.
 player query_property  is net dead.
 Insufficient Social Points.
 ing
  tells you event_person_tell	 You tell   asks you:  You ask  /global/player emote" You do not have that ability yet.
 Syntax: emote <womble>

 %^RESET%^
 Syntax : shout <text>
 query_earmuffs1 Why shout when you can't hear people shout back?
 shouts s person_shout	 You shout' Syntax: whisper [to] <person> <string>
 to %s  whispers to  query_objective self.
 Whispering to your self!?
% Could not find anyone to whisper to.
	 %^RESET%^ whisper  whispers to You whisper  to  global/do_chat do_chat sh r rr in' x xsh S SH R RR test_language gruntF You just forgot the language you were speaking.  You are now speaking  .
 You are now speaking   and can speak any of  You do not know 
 Now using   for speaking and writing.
 social_points max_social_points
 guild_flag my_file_name	 languages cur_lang drunk_speech communicate_commands set_max_social_points query_max_social_points set_social_points query_social_points adjust_social_points hard_adjust_social_points query_word_type query_shout_word_type query_whisper_word_type my_mess do_loud_say do_say do_tell do_emote do_shout
 do_whisper do_channels add_language remove_language set_language query_current_language query_languagesLL         %  
      � d e f g h i j k l m n o p q r s t 	x z 	{ | 	~ � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � 	� 	� 	� � � 	� � � � 	� � � � � � � � � � 	� 	� 	� � � �  	 "#
$	%&	'(*+,./234678:;<>?@	A	BCDEDDEFGHJKJJ
KLMN	PQXYZ\]_abcfgh	jprst����������������	����	�	���������	��������
��������	������	������	�	��	�����	��	���� 
 "#$&'(+-  