MUDB!��0#��0 include/ed.h  global/line_ed.c@  �'             P      x�
 h�
 ����|  �	  �
  ��@  ����        , V      8T(v(5 V" (58T5
 g8T 58T5  7 T6#� � � 5 m >8 TV" 6 h8T	6	;�
t	(5 � 5 * d^;;5 �d^;;]
	(5 m >8 TV" 6 h8T	6	;�
t	($   s    I    � (5 *� 	d5 7 T5 
 ) 5 
#���V" t(V" t(7T7T 5	;56 
�7<56 h, d^d5^(V" t(6	;�V" 6 h8T
t(V" d^;;6 n�d^;;]
(V" 6 n& ( V" !t("�7Td^d5^(#6) $ %;&;V" &  ($C   tD   E   �H   �I   L   +M   fQ   �S   �c   td   e   �h   �i   l   +m   fq   �s   �6) 6 h';V" (t 	6	;�
t((d^&  (5 )W7T7T)p 55. 57T57T57T5	,
 56 h	;. *V" &  +5;,;5;-;V" 6 5	>55>	;V 8 T.V" &  (5 /W7T	)M 5	, 56 h. 0V" &  (15;-;V" 6 5	>	V 8 T.V" &  (25 ;-;V" &  ((5 /W7T	* 3V" &  (5	,
 56 h	;. 4V" &  (5	>8T55;6;7;V" 
t((5 h	. 5 
~) 6) 	�  5 &  (5 8)/ 6) &   6 h 6 n&  & (6	>6 5  ;6�  6 ;8 T8/	6	;�
t((5 )W7T7T)d 55. 57T57T57T5	,
 56 h	;. *V" &  95;,;5;-;V" :V" 58T58T;t(5 /W7T	)E 5	, 56 h. 0V" &  (<5;-;V" :V" ;t58S8T(25 ;-;V" &  ((5 F 5 ) =V" &  (>V" ?t5 8T((@6;A;5 ;B;C;6;D;6;-;V" 6	>7Td 56 
E6;E;W7T7T)G 5 7<
 55 ;7<5E6;E;W7T7T) 55;58 9T5	;56 
�V" 56,h FV" &  ((d^;;�7 Td^;;� GHd^;;;V	 I5 ;I;m8 T	�  6 
8 9T6 h	>6 
h>6 h	>6 
6 h	>8 9T&  ((d^;;�7 Td^;;� GHd^;;;V	 5  JV" & (5 m8 T6 h 5 &  & ((  8 T665 ^8T(5 * 5 
y*	 5 
Y* KV" &  (LV" & 8T((5  s) MV (5 8TN5 ;-;V" 	((dO^7 TP5 
 QRSP5 
^TV ;;(((6# UV" 6* 6 n&  &  ( �
  �      �'  L      ��           (        (         H'  �    �(  �    �(  �     �      �(  �     t*  �    �*  �     )  `     �&  �     L%  a     @  �     d+  �      �+     �' �& �' @ �' �\ h| �� �� 0( � l l <� D( �& X( �P $' �( �� �( � H' �( l �P �( �Q 8�
 ) �&  R L%  ) 8W < | � ��
 �
 l( D) `) � �� �( �} $Q �) �) LQ �) �) ] ��
 � P* % t* �*  �* �* ��
 �*  �*  � L + H+ �
 \ � 0�
 � t�
 �+ �+ �  + �+ ( , X�
 � C �
   T
 D ' K�'   * T  * 	[4*  	�    �   global/line_ed.c include/ed.h menu
 set_editor editor Someone has stuffed up.
   
6 Ok, enter your text.  ** on a line by itself to exit.
 %-2d]  editor_loop ed /tmp/board.
 query_name .tmp editor_finish_ed commandD Ok, enter your text.  ** on a line by itself to quit.  ~h for help.
 Insert before line :  editor_insert$ Delete (line no, or n..m ie 1..2) :  editor_delete %3d: %s
 end_of_edit_more set_finish_func more_string/ Modify which line (line no, or n..m ie 1..2) :  editor_modifyD Ok, back into insertion mode, ** on a line by itself to exit.
%-2d] n Entering ed....  Use 'q' to quit, 'x' to save and exit, 'Q' to quit without saveing changes and 'h' for help.
 editor_exit_ed Quiting and saving.
% Are you sure you want to quit (Y/N)?  editor_check_quit /doc/helpdir/edit_help I do not understand you.  Try  ~h h  for help.
*  lines - Choose from IDLMCESQ H for help.  main_bit %d..%d Out of bounds.
 Deleteing from line 	  to line  .
 Ok.
 %d Line number out of range.
 Deleteing line  Error, invalid data  ERROR! Must be a number.
 Number out of bounds.
 Inserting before line $ .  Entering insertion mode, ** on a  line by itself to exit
]  ** Modifying from line  Text to change ?  editor_modify2 Modifying line 
 Aborting.
 Change to ?  editor_modify3 Changing all occurances of ' ' to ' '  from   to  %s Done.
 /save/board/LOG ed: couldn't rm /tmp/board. #	 Aborted.
 Returing to the editor.
	 Quiting.
� Your editor can be set to one of the following menu, ed and command.  Please do not set your editor to ed unless you know what you are doing.  The menu editor is the default and the command editor is based on using ~ escape characters.
 Editor set to  query_aliases
 .signature 
--
 /secure/finger make_string ; Saveing what you are editing.
 lines end_func
 end_object insertion_point editor range1 range2 modify_string main_bit editor_do_quit create editor_commands do_edit end_of_edit_more editor_delete editor_insert editor_loop editor_modify editor_modify2 editor_modify3 editor_exit_ed editor_finish_ed editor_check_quit
 set_editor append_signature editor_check_do_quit��     |  	 " # $ & ' ( * + , 
- / 0 1 	2 3 4 6 7 8 9 ; < = 	> ? @ H J 
I K N O P S T U X Y Z Y 	[ 	\ ] ` a b e f g h i l o p q t 
u v y z { ~ 	 	� � � � � � o� � � � 	� � � � 	� � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � � 
� � � � � � � 	� � � � � � � � � � � � � � � � � � � � �  	

 !#"$%
'()/012345467=>?@ABCEF
GIJN	OPTUVWYZ[\`afhij	pqrrsuy{|} A 