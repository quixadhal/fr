/* Excluding this from the soul.c, just to make things a little cleaner */
/* Wonderflug, 1996 */

global_adj = 
",slowly,happily,sadly,nervously,wryly,broadly,crookedly,"+
"stupidly,idiotically,condescendingly,ironically,patiently,brightly,"+
"slightly,nastily,excitedly,strangely,with forced patience,plasticly,"+
"carefully,sadisticly,lopsidedly,fishily,catishly,faintly,"+
"like a duck,angrily,paranoicaly,innocently,frogily,slyly,"+
"weakly,humbly,paradoxically,sarcasticly,viciously,garishly,"+
"sweetly,innocently,lovingly,dreamily,radiantly,enthusiasticly,"+
"insolently,quirkily,completely,unconsciously,drunkenly,"+
"insanely,cutely,maliciously,maybe,fleetingly,"+
"absentmindedly,curtly,disturbingly,unbelievably,quietly,"+
"loudly,differently,winningly,in triumph,seductively,"+
"tightly,because of all the arguments,softly,positively,"+
"lividly,demonically,warmly,coldly,drunkenly,negatively,"+
"manically,warily,sardonically,lazily,serenely,disappointedly";
soul_data =
([ 
  "ack" : ({ ({ 0, "%s", 0, "at %s" }),
    ({ "You ack",
      "$mcname$ ack's",
      "You ack at $hcname$",
      "$mcname$ ack's at you",
      "$mcname$ ack's at $hcname$", }) }),
  "accuse" : ({ ({ 0, "%s", 2, "%s of %s", 2, "%s %s", 3, "%s" }), ({
      "$ifarg:You accuse $arg:#$$else$The butler did it!~$", 
      "$mcname$ $ifarg:accuses $lastarg$$else$accuses the butler~$",
      "You accuse $hcname$$ifarg: of $arg:#$~$",
      "$mcname$ accuses you$ifarg: of $lastarg$~$",
      "$mcname$ accuses $hcname$$ifarg: of $lastarg$~$" }) }),
  "admire" : ({ ({ 0, "%s", 2, "%s %s", 3, "%s" }), ({
      "$ifarg:You admire $arg:#$$else$You admire this wonderful MUD!~$",
      "$mcname$ $ifarg:admires $lastarg$$else$admires this wonderful MUD~$",
      "You admire $hcname$$ifarg: for being $arg:#$~$",
      "$mcname$ admires you$ifarg: for being $lastarg$~$",
      "$mcname$ admires $hcname$$ifarg: for being $lastarg$~$" }) }),
  "apologize" : ({
    ({ 3, "%s", 1, "%s to %s", 1, "%s %s", 2, "%s %s", }), ({
      "You apologize $arg:profusely,happily,sadly,reservedly,"+
      "carefully,slowly,perfunctorily,curtly,viciously,"+
      "sulkily,drunkenly,unhappily,professionally,pompously,"+
      "wholeheartedly,partially,wearily,fishily,facetiously,"+
      "unnecessarily,spontaneously,twice,thoroughly,humbly$",
      "$mcname$ apologizes $lastarg$",
      "You apologize $arg:profusely,happily,sadly,reservedly,"+
      "carefully,slowly,perfunctorily,curtly,viciously,"+
      "sulkily,drunkenly,unhappily,professionally,pompously,"+
      "wholeheartedly,partially,wearily,fishily,facetiously,"+
      "unnecessarily,spontaneously,twice,thoroughly,humbly$"+
      " to $hcname$",
      "$mcname$ apologizes $lastarg$ to you",
      "$mcname$ apologizes $lastarg$ to $hcname$" }) }),
  "applaud" : ({
    ({ 0, "%s", 1, "%s %s", 2, "%s %s", 3, "%s" }), ({
      "You applaud $arg:wholeheartedly,loudly,softly,vaguely,briefly$",
      "$mcname$ applauds $lastarg$",
      "You applaud $hcname$ $arg:wholeheartedly,loudly,softly,vaguely,briefly$",
      "$mcname$ applauds you $lastarg$",
      "$mcname$ applauds $hcname$ $lastarg$" }) }),
  "astound" : ({ ({ 0, "%s" }), ({
      "You are astounded!",
      "$mcname$ is astounded!",
      "You astound $hcname$$ifarg:with your $arg:stupidity,cleverness"+
      ",thoughtfulness$~$!",
      "$mcname$ astounds you$ifarg: with $mposs$ $lastarg$~$!",
      "$mcname$ astounds $hcname$$ifarg: with $mposs$ $lastarg$~$" }) }),
  "agree" : ({ ({ 0, "%s", 0, "with %s", 1, "%s with %s", 1, "%s %s",
      2, "with %s %s", 3, "%s" }), ({
      "You agree $arg:wholeheartedly,partially,wearily,to some degree$",
      "$mcname$ agrees $lastarg$",
      "You agree $arg:wholeheartedly,partially,wearily,"+
      "to some degree$ with $hcname$",
      "$mcname$ agrees $lastarg$ with you",
      "$mcname$ agrees $lastarg$ with $hcname$" }) }),
  "bark" : ({ ({ 3, "%s" }), ({
      "You bark like a $arg:dog,cat,tree,duck,wolf,hunting dog,labrador,"+
      "german shepard,something else that barks,"+
      "bull terrier,train$",
      "$mcname$ barks like a $lastarg$", }) }),
  "beam" : ({ ({ 3, "%s", 1, "%s at %s", 1, "%s %s", 2, "at %s %s",
      2, "%s %s", 0, "%s" }), ({
      "You beam $arg:brightly,admiringly,strangely,happily,ecstatically,fishily,"+
      "like a train$",
      "$mcname$ beams $lastarg$",
      "You beam at $hcname$$ifarg: $arg:brightly,admiringly,strangely,happily,"+
      "ecstatically,fishily,like a duck with an open beak,like a train$~$",
      "$mcname$ beams at you$ifarg: $lastarg$~$",
      "$mcname$ beams at $hcname$$ifarg: $lastarg$~$", }) }),
  "beep" : ({ ({ 3, "%s" }), ({
      "You beep $arg:happily,#$",
      "$mcname$ beep $arg:happily,#$" }) }),
  "beg" : ({ ({
      0, "at %s", 0, "%s", 2, "at %s %s", 2, "at %s like a %s",
      1, "like a %s at %s", 1, "%s at %s", 1, "%s %s", 1, "%s %s",
      3, "%s", 3, "like a %s", }), ({
      "You beg like a $arg:dog,cat,frog,chicken,frisbee,cow,large bear,"+
      "poodle,chihuahua,train,beggar,noble man,lassie,labrador,german shepard,"+
      "cannibal,chimpanzee,orang-u-tang,librarian,fish,dolphin,toxic,"+
      "banshee,bloodhound,st bernard,virgin mary,husky,wolf,dingo,alsation$",
      "$mcname$ begs like a $lastarg$",
      "You beg like a $arg:dog,cat,frog,chicken,frisbee,cow,large bear,"+
      "poodle,chihuahua,train,beggar,noble man,lassie,labrador,german shepard,"+
      "cannibal,chimpanzee,orang-u-tang,librarian,fish,dolphin,toxic,"+
      "banshee,bloodhound,st bernard,virgin mary,husky,wolf,dingo,alsation,"+
      "train$ at $hcname$",
      "$mcname$ begs like a $lastarg$ at you",
      "$mcname$ begs like a $lastarg$ at $hcname$", }) }),
  "bing" : ({ ({ 0, "at %s", 0, "%s", 1, "%s at %s", 1, "%s %s", 2, "%s %s",
      2, "at %s %s", 3, "%s" }), ({
      "You bing $arg:happily,sadly,joyfully,sagely,knowingly,quickly,"+
      "loudly,carefully,balefully,excitedly,nervously,brightly,"+
      "uncertainly$",
      "$mcname$ bings $lastarg$",
      "You bing $arg:happily,sadly,joyfully,sagely,knowingly,quickly,"+
      "excitedly,nervously,brightly,uncertainly,"+
      "loudly,carefully,balefully$ at $hcname$",
      "$mcname$ bings $lastarg$ at you",
      "$mcname$ bings $lastarg$ at $hcname$" }) }),
  "bingf" : ({ ({ 0, "at %s", 0, "%s", 1, "%s at %s", 1, "%s %s", 2, "%s %s",
      2, "at %s %s", 3, "%s" }), ({
      "You bing in a $arg:sarcastically,sadly,joyfully,sagely,knowingly,"+
      "quickly,"+
      "loudly,carefully,balefully,excitedly,nervously,brightly,"+
      "uncertainly$ but formatted way",
      "$mcname$ bings in a $lastarg$ but formatted way",
      "You bing in a $arg:sarcastically,sadly,joyfully,sagely,knowingly,"+
      "quickly,"+
      "loudly,carefully,balefully,excitedly,nervously,brightly,"+
      "uncertainly$ but formatted way with $hcname$",
      "$mcname$ bings in a $lastarg$ but formatted way with you",
      "$mcname$ bings in a $lastarg$ but formatted way with $hcname$", }) }),
  "bird" : ({ ({ 0, "%s" }), ({
      "You raise your middle finger and give $hcname$ the bird",
      "$mcname$ raises $mposs$ middle finger and gives you the bird",
      "$mcname$ raises $mposs$ middle finger and gives $hcname$ the bird" }) }),
  "bite" : ({ ({ 0, "%s", 2, "%s %s", 1, "%s %s" }), ({
      "You bite yourself",
      "$mcname$ bites $mobj$self",
      "You bite $hcname$$ifarg: $arg:hard,nastily,carefully,politely,fishily,"+
      "lovingly,refreshingly,happily,like a train,pointlessly,"+
      "objectively,sulkily,gently,brightly,excitedly,uncertainly,"+
      "like a dog,wolfishly,mercilessly,ruthlessly,softly,sweetly,"+
      "professionally,hungrily,mischievously,ankles,arm,leg,casually,"+
      "nose,ear,toe,finger$~$",
      "$mcname$ bites you$ifarg: $lastarg$~$",
      "$mcname$ bites $hcname$$ifarg: $lastarg$~$", }) }),
  "bleed" : ({ ({ 3, "%s" }), ({
      "$ifarg:Your $arg:heart,leg,arm,head,ear,nose,profusely"+
      "$ bleeds$else$You bleed~$",
      "$ifarg:$mcname$'s $lastarg$ bleeds$else$$mcname$ bleeds~$", }) }),
  "blink" : ({ ({ 3, "%s" }), ({
      "You blink$ifarg: $arg:owlishly,slowly,carefully$~$",
      "$mcname$ blinks$ifarg: $lastarg$~$" }) }),
  "blush" : ({ ({ 3, "%s" }), ({
      "You blush $arg:in embarrassment,redly,slightly,worriedly$",
      "$mcname$ blushes $lastarg$" }) }),
  "boggle" : ({ ({ 3, "%s", 0, "at %s", 0, "%s" }), ({
      "You boggle at $arg:the concept,#$", "$mcname$ boggles at $lastarg$",
      "You boggle at $hcname$",
      "$mcname$ boggles at you",
      "$mcname$ boggles at $hcname$", }) }),
  "bonk" : ({ ({ 0, "%s" }), ({
      "B O N K !",
      "$mcname$ goes B O N K !",
      "You bonk $hcname$ on the head",
      "$mcname$ bonks you on the head",
      "$mcname$ bonks $hcname$ on the head" }) }),
  "bop" : ({ ({ 0, "%s" }), ({
      "You bop to the beat",
      "$mcname$ bops to the beat",
      "You bop $hcname$ on the head", 
      "$mcname$ bops you on the head",
      "$mcname$ bops $hcname$ on the head" }) }),
  "bounce" : ({ ({ 0, "%s", 1, "%s around %s", 1, "%s %s", 2, "%s %s", 3, "%s" }), ({
      "$ifarg:You bounce around $arg:excitedly,like a duck,fearfully,happily$"+
      "$else$B O U N C E ! !~$",
      "$mcname$ bounces around$ifarg: $lastarg$~$",
      "You bounce around $hcname$$ifarg: $arg:happily,carefully,wildly,"+
      "excitedly,pinkly,joyfully,once,slowly,suggestively,"+
      "happily,womblely$~$",
      "$mcname$ bounces around you$ifarg: $lastarg$~$",
      "$mcname$ bounces around $hcname$$ifarg: $lastarg$~$", }) }),
  "breakdance" : ({ 0, ({
      "You do a really complicated break-dance manoeuvre",
      "$mcname$ does a really complicated-break dance manoeuvre", }) }),
  "breathe" : ({ ({ 3, "%s", }), ({
      "You breathe $arg:quickly,seductively,painfully,nastily,slowly,once,"+
      "heavily,carefully,heatedly$",
      "You breathe $lastarg$", }) }),
  "burp" : ({ ({ 3, "%s" }), ({
      "You burp$ifarg: $arg:disgustingly,faintly,loudly,rudely$~$",
      "$mcname$ burps$ifarg: $lastarg$~$" }) }),
  "bow" : ({ ({ 0, "%s", 0, "to %s", 1, "%s to %s", 1, "%s %s", 3, "%s" }), ({
      "You bow$ifarg: $arg:solemnly,deeply,formally,hastily,slightly," +
      "insolently,clumsily,dexterously,wildly,colorfully$~$",
      "$mcname$ bows$ifarg: $lastarg$~$",
      "You bow$ifarg: $arg:solemnly,deeply,formally,hastily,slightly,"+
      "insolently,clumsily,dexterously,wildly,colorfully$~$ to $hcname$",
      "$mcname$ bows$ifarg: $lastarg$~$ to you",
      "$mcname$ bows$ifarg: $lastarg$~$ to $hcname$" }) }),
  "bubble" : ({ ({ 0, "%s", 0, "at %s" }), ({
      "You're bubbling over with joy!",
      "$mcname$ bubbles over with joy.",
      "You blow bubbles at $hcname$",
      "$mcname$ blows bubbles at you",
      "$mcname$ blows bubbles at $hcname$" }) }),
  "burn" : ({ ({ 0, "%s", 1, "%s %s", 2, "%s %s" }), ({
      "You set fire to yourself",
      "$mcname$ sets fire to $mobj$self",
      "You set fire to $mhcname$ $arg:hair,leg,arm,nose,teeth,feathers,carpet,"+
      "net lag,fish,invis,bed,ego,eyes,house,furniture,tongue,keyboard,"+
      "brain,code,ideas,hopes,dreams,cat,personality,desires,beliefs$",
      "$mcname$ sets fire to your $lastarg$",
      "$mcname$ sets fire to $mhcname$ $lastarg$", }), }),
  "cackle" : ({ ({ 3, "%s" }), ({
      "You cackle $ifarg:$arg:with glee,maniacally,mischievously,nastily,"+
      "despairingly,womblely,backwards$$else$with glee~$",
      "$mcname$ $ifarg:cackles $lastarg$$else$"+
      "throws back $mposs$ head and cackles with glee~$" }) }),
  "calm" : ({ ({ 0, "%s", 0, "%s down" }), ({
      "You calm down",
      "$mcname$ calms down",
      "You calm $hcname$ down",
      "$mcname$ calms you down",
      "$mcname$ calms down $hcname$", }) }),
  "caper" : ({ ({ 3, "%s" }), ({
      "You caper around$ifarg: like a $arg:fool,chicken,womble,jester,"+
      "bimbo,blonde,sulam,seductress,eager person,vivacious person,"+
      "madman,madwomen,madperson,duck on the run,"+
      "happy chap,polite gentleperson,woman,nympho$"+
      "$else$ madly~$", /* giggle */
      "$mcname$ capers around$ifarg: like a $lastarg$$else$ madly~$", }) }),
  "caress" : ({ ({ 0, "%s", 2, "%s %s", }), ({ 
      "You caress $hcname$$ifarg: $arg:gently,strangely,violently,"+
      "firmly,seductively,suggestively,slightly,sensually,"+
      "reluctantly,politely,lovingly,vigorously,eagerly,vivaciously$~$",
      "$mcname$ caresses you$ifarg: $lastarg$~$",
      "$mcname$ caresses $hcname$$ifarg: $lastarg$~$", }) }),
  "challenge" : ({ ({ 0, "%s", }), ({
      "Make your own challenges to $hcname$",
      "You make your challenges to $mcname$",
      "$mcname$ challenges $hcname$", }) }),
  "cheer" : ({ ({ 0, "%s", 0, "at %s", 1, "%s at %s", 1, "%s %s", 2, "at %s %s", 3, "%s" }),
    ({
      "You cheer $arg:enthusiasticly,excitedly,quietly,calmly,carefully,"+
      "politely,wildly,oddly,unconvincingly,happily,slightly,up$",
      "$mcname$ cheers $lastarg$",
      "You cheer $arg:enthusiasticly at,excitedly at,quietly at,calmly at,"+
      "wildly at,unconvincingly at,carefully at,happily at,"+
      "politely at,oddly at,slightly at,up$ $hcname$",
      "$mcname$ cheers $lastarg$ you",
      "$mcname$ cheers $lastarg$ $hcname$", }) }),
  "choke" : ({ ({ 0, "%s" }), ({
      "You choke",
      "$mcname$ chokes",
      "You choke $hcname$",
      "$mcname$ chokes you",
      "$mcname$ chokes $hcname$$force#breath pain#2$" }) }),
  "chuckle" : ({ ({ 3, "%s" }), ({
      "You chuckle $arg:politely,nastily,demonically$",
      "$mcname$ chuckles $lastarg$" }) }),
  "clap" : ({ ({ 3, "%s" }), ({
      "You clap your hands $arg:briefly,loudly,enthusiasticly,halfheartedly$",
      "$mcname$ claps $mposs$ hands $lastarg$" }) }),
  "comfort" : ({ ({ 0, "%s", 1, "%s %s", 2, "%s %s" }), ({
      "You comfort $hcname$$ifarg: $arg:sincerely,wholeheartly,mischievously,"+
      "halfheartedly,vaguely,eagerly,completely,lovingly,gently,"+
      "tenderly,sadly,in earnest,with your wings,in the ear,in the leg,"+
      "twice,anxiously,carefully,delicately,like someone else$~$",
      "$mcname$ comforts you$ifarg: $lastarg$~$",
      "$mcname$ comforts $hcname$$ifarg: $lastarg$~$" }) }),
  "confess" : ({ ({ 3, "%s" }), ({
      "I confess $ifarg:$arg:#$$else$to being a witch~$",
      "$mcname$ confess's $ifarg:$lastarg$$else$to being a witch, burn "+
      "$mposs$~$", }), }),
  "congrat" : ({ ({ 0, "%s", 1, "%s %s", 2, "%s %s" }), ({
      "You$ifarg: $arg:heartily,warmly$~$ congratulate everyone",
      "$mcname$$ifarg: $lastarg$~$ congratulates everyone",
      "You$ifarg: $arg:heartily,warmly$~$ congratulate $hcname$",
      "$mcname$$ifarg: $lastarg$~$ congratulates you",
      "$mcname$$ifarg: $lastarg$~$ congratulates $hcname$" }) }),
  "cough" : ({ 0, ({ "You cough", "$mcname$ coughs" }) }),
  "cow" : ({ ({ 0, "%s", 1, "%s %s", 2, "%s %s", 3, "%s" }), ({
      "You graze around $arg:mindlessly,silently,happily,carefully,#$",
      "$mcname$ grazes around $lastarg$",
      "You turn $hcname$ into a cow$ifarg: $arg:slowly,carefully,"+
      "excruciatingly,happily,gleefully,magicly$~$",
      "$mcname$ turns you into a cow$ifarg: $lastarg$~$",
      "$mcname$ turns $hcname$ into a cow$ifarg: $lastarg$~$"+
      "$force#moo#2$" }) }),
  "cower" : ({ ({ 3, "%s" }), ({
      "You cower $arg:in a corner,fearfully,slyly,shyly,in shame,"+
      "nastily$",
      "$mcname$ cowers $lastarg$", }), }),
  "cringe" : ({ 0, ({
      "You cringe$ifarg: in $arg:terror,embarrassment$~$",
      "$mcname$ cringes$ifarg: in $lastarg$~$" }) }),
  "croak" : ({ 0, ({
      "Ribbit",
      "$mcname$ croaks (ribbit)" }) }),
  "cross" : ({ ({ 3, "%s", 3, "my %s" }), ({
      "You cross your $arg:fingers,legs,eyes$",
      "$mcname$ crosses $mposs$ $lastarg$", }) }),
  "crowd" : ({ ({ 0, "%s", 1, "%s %s", 2, "%s %s", 2, "%s into %s",
      3, "%s" }), ({
      "The crowd goes $arg:wild,#$",
      "The crowd goes $arg:wild,#$",
      "You crowd $hcname$ into $arg:a corner,#$",
      "$mcname$ crowds you into $lastarg$",
      "$mcname$ crowds $hcname$ into $lastarg$" }) }),
  "cry" : ({ 0, ({ "Wahhhhhh", "$mcname$ crys loudly" }) }),
  "cuddle" : ({ ({ 0, "%s", 1, "%s %s", 2, "%s %s" }), ({
      "You cuddle $hcname$",
      "$mcname$ cuddles you",
      "$mcname$ cuddles $hcname$" }) }),
  "curse" : ({ ({ 0, "%s", 1, "%s %s",  1, "%s at %s", 2, "at %s %s",
      2, "%s %s" , 3, "%s" }), ({
      "You curse$ifarg: $arg:loudly,strongly,rudely,unashamedly,#$~$",
      "$mcname$ curses$ifarg: $lastarg$~$",
      "You curse$ifarg: $arg:loudly,strongly,rudely,unashamedly,#$~$ at "+
      "$hcname$",
      "$mcname$ curses$ifarg: $lastarg$ at~$ you",
      "$mcname$ curses$ifarg: $lastarg$~$ at $hcname$" }) }),     
  "curtsey" : ({ ({
      0, "%s", 0, "to %s", 0, "before %s", 1, "%s %s",
      2, "%s before %s", 2, "%s to %s",3, "%s" }), ({
      "You curtsey$ifarg: $arg:gracefully,humbly,quickly,low,slightly$~$",
      "$mcname$ curtsies$ifarg: $lastarg$~$",
      "You curtsey$ifarg: $arg:gracefully,humbly,quickly,low,slightly$~$ to $hcname$",
      "$mcname$ curtsies$ifarg: $lastarg$~$ before you",
      "$mcname$ curtsies$ifarg: $lastarg$~$ to $hcname$" }) }),
  "dance" : ({ ({ 0, "%s", 0, "with %s" }), ({
      "You do the disco duck.  Feels great doesn't it ?",
      "$mcname$ dances the disco duck",
      "You sweep $hcname$ across the dance floor",
      "$mcname$ sweeps you across the dance floor",
      "$mcname$ sweeps $hcname$ across the dance floor" }) }),
  "daydream" : ({ ({ 3, "%s", }), ({
      "You daydream$ifarg: of $arg:#$~$",
      "$mcname$ daydreams$ifarg: of $lastarg$~$", }) }),
  "die" : ({ ({0, "%s",  1, "%s %s",
      1, "%s at %s", 2, "%s %s",
      2, "at %s %s",  3, "%s" }),  ({
      "You die $arg:suddenly,dramatically,of boredom,of hunger,of "+
      "anticipation,pathetically,gracefully,senselessly,stupidly,"+
      "tragically,slowly,painfully,an excruciating death$",
      "$mcname$ dies $lastarg$",
      "You die$ifarg: $arg:suddenly,dramatically,of boredom,of hunger,of "+
      "anticipation,pathetically,gracefully,senselessly,stupidly,"+
      "tragically,slowly,painfully,an excruciating death$~$"+
      " in $mhcname$ general direction",
      "$mcname$ dies$ifarg: $lastarg$~$ in your general direction",
      "$mcname$ dies$ifarg: $lastarg$~$ in $mhcname$ general direction" }) }),
  "dribble" : ({ ({0, "%s", 0, "on %s", 0, "all over %s"  }), ({
      "You start to dribble all over the front of your shirt",
      "$mcname$ starts to dribble all over the front of $mposs$ shirt",
      "You start dribbling on $hcname$",
      "$mcname$ starts dribbling all over your best shirt",
      "$mcname$ starts dribbling all over $hcname$" }) }),
  "drool" : ({ ({ 0, "%s", 0, "at %s" }), ({
      "You start to drool",
      "$mcname$ starts to drool",
      "You drool all over $hcname$",
      "$mcname$ drools all over you",
      "$mcname$ drools all over $hcname$" }) }),
  "duck" : ({ 0, ({
      "You duck for cover",
      "$mcname$ ducks for cover" }) }),
  "duh" : ({ 0, ({
      "You scream \"Duh!\"",
      "$mcname$ screams \"Duh!\"", }) }),
  "eye" : ({ ({ 0, "%s" }), ({
      "You eye $hcname$ over",
      "$mcname$ eyes you over",
      "$mcname$ eyes $hcname$ over", }), }),
  "exp" : ({ ({ 0, "%s", 1, "%s %s", 2, "%s %s", 3, "%s" }), ({
      "You raise yourself to the power of$ifarg: $arg:#$~$",
      "$mcname$ raises $mobj$self to a random power",
      "You raise $hcname$ to the power of$ifarg: $arg:#$~$",
      "$mcname$ raises you to the power of$ifarg: $lastarg$~$",
      "$mcname$ raises $hcname$ to the power of$ifarg: $lastarg$~$" }) }),
  "expect" : ({  ({ 0, "%s", 0, "at %s" }), ({
      "You look at expectantly at $hcname$",
      "$mcname$ looks expectantly at you",
      "$mcname$ looks expectantly at $hcname$" }) }),
  "explode" : ({ 0, ({
      "You explode into thousands of tiny pieces",
      "$mcname$ explodes into thousands of tiny pieces", }) }),
  "faint" : ({ ({ 3, "%s", 0, "%s" }), ({
      "You faint$ifarg: $arg:tiredly,out of boredom$~$",
      "$mcname$ faints$ifarg: $lastarg$~$",
      "You faint on $hcname$",
      "$mcname$ faints on you",
      "$mcname$ faints on $hcname$" }) }),
  "fart" : ({ 0, ({ /* don't like this emote, can you tell?? */ /* yes :) */
      "You fart",
      "$mcname$ farts" }) }),
  "fiddle" : ({ 0, ({
      "You fiddle with something",
      "$mcname$ fiddles with something", }), }),
  "fish" : ({ ({
      0, "%s", 0, "in %s", 1, "for %s in %s pockets",
      1, "for %s in %s", 1, "%s in %s", 2, "%s %s", 3, "%s" }), ({
      "You fish around in your pockets$ifarg: for a $arg:#$~$",
      "$mcname$ fishes around in $mposs$ pockets$ifarg: for a $lastarg$~$",
      "You fish around in $mhcname$ pockets$ifarg: for a $arg:#$~$",
      "$mcname$ fishes around in your pockets$ifarg: for a $lastarg$~$",
      "$mcname$ fishes around in $mhcname$ pockets$ifarg: for a $lastarg$~$" }) }),
  "flap" : ({ ({ 3, "%s" }), ({
      "You flap your $arg:ears,arms,wings,eyelashes$",
      "$mcname$ flaps $mposs$ $arg:ears,arms$" }) }),
  "flex" : ({ ({ 3, "%s" }), ({
      "You flex your $arg:muscles,biceps,triceps,legs,brain,nose,ears$",
      "$mcname$ flexes $mposs$ $lastarg$", }) }),
  "flip" : ({  ({ 3, "%s", 0, "%s", 1, "%s %s", 2, "%s %s" }), ({
      "You flip $arg:head over heels,backwards,forwards,sideways,"+
      "around,carefully,slowly,twice,doggily,awkwardly,disturbingly,"+
      "disgustingly,quickly,slowly,gracefully,over the moon,"+
      "around in a really complicated double back roll flip,"+
      "half way around and land on your head, ouch$",
      "$mcname$ flips $lastarg$",
      "You flip $hcname$ $arg:head over heels,off,into the garbage bin,"+
      "visciously,dangerously,spectacularly$",
      "$mcname$ flips you $lastarg$",
      "$mcname$ flips $hcname$ $lastarg$" }) }),
  "flop" : ({ ({ 3, "%s" }), ({
      "You flop about $arg:helplessly,like a fish out of water,"+
      "badly,like zoroaster,carefully,rudely,a bit,once,like a gherkin,wonderfully,"+
      "impressively,suggestively,lazily,happily,pensively$",
      "$mcname$ flops about $lastarg$" }) }),
  "flustered" : ({ 0, ({
      "You look flustered",
      "$mcname$ looks flustered", }) }),
  "fondle" : ({ ({ 0, "%s", 1, "%s %s" }), ({
      "You fondle $ifarg:$mhcname$ $arg:#$$else$$hcname$~$",
      "$mcname$ fondles$ifarg: with your $lastarg$$else$ you~$",
      "$mcname$ fondles $ifarg:with $mhcname$ $lastarg$$else$$mhcname$~$" }) }),
  "foo" : ({ ({ 3, "%s" }), ({
      "You foo $arg:vaguely,carefully,slowly,dangerously$",
      "$mcname$ foos $lastarg$", }), }),
  "forgive" : ({ ({ 0, "%s", }), ({
      "You forgive $hcname$",
      "$mcname$ forgives you",
      "$mcname$ forgives $hcname$", }), }),
  "frog" : ({ ({ 0, "%s", 1, "%s %s", 2, "%s %s", 3, "%s" }), ({
      "You frog around $arg:mindlessly,silently,happily,carefully,#$",
      "$mcname$ frogs around $lastarg$",
      "You turn $hcname$ into a frog$ifarg: $arg:slowly,carefully,"+
      "excruciatingly,happily,gleefully,magicly$~$",
      "$mcname$ turns you into a frog$ifarg: $lastarg$~$",
      "$mcname$ turns $hcname$ into a frog$ifarg: $lastarg$~$"+
      "$force#croak#2$" }) }),
  "french" : ({ ({ 0, "%s" }), ({
      "You give $hcname$ a deep and passionate kiss, it seems to last forever..",
      "$mcname$ gives you a deep and passionate kiss, it seems to last forever..",
      "$mcname$ gives $hcname$ a deep and passionate kiss, it seems to last forever.." }) }),
  "froth" : ({ 0, ({
      "You froth at the mouth",
      "$mcname$ froths at the mouth" }) }),
  "frown" : ({ ({ 3, "%s", 3, "in %s" }), ({
      "$ifarg:You frown in $arg:concentration,thought,anger,"+
      "depression,like a cat,happily,#$$else$Whats the problem?~$",
      "$ifarg:$mcname$ frowns in $lastarg$$else$$mcname$ frowns~$" }) }),
  "fume" : ({ ({ 3, "%s", }), ({
      "You fume $arg:quietly,insultingly,despairingly$",
      "$mcname$ fumes $lastarg$", }) }),
  "gasp" : ({ ({ 3, "%s", 3, "in %s", }), ({
      "You gasp in $arg:astonishment,excitement,terror,fear,fright,pain$",
      "$mcname$ gasps in $lastarg$" }) }),
  "gesticulate" : ({ 0, ({
      "You gesticulate wildly",
      "$mcname$ gesticulates wildly" }) }),
  "gibber" : ({ 0, ({
      "You gibber madly",
      "$mcname$ gibbers madly", }) }),
  "giggle" : ({ ({ 3, "%s" }), ({
      "You giggle$ifarg: $arg:inanely,loudly,stupidly, "+
      "quietly,idioticly,fiendishly$~$",
      "$mcname$ giggles$ifarg: $lastarg$~$" }) }),
  "glare" : ({ ({
      0, "%s", 0, "at %s", 1, "%s at %s", 2, "at %s %s",
      1, "%s %s", 2, "%s %s", 3, "%s" }), ({
      "You glare $arg:stonily,sternly,hotly,intently,solemnly,idioticly,evenly,"+
      "evilly$ at the world in general",
      "$mcname$ glares $lastarg$ around $mpronoun$",
      "You glare $arg:stonily,sternly,hotly,intently,solemnly,evilly,evenly,"+
      "idiotically$ at $hcname$",
      "$mcname$ glares $lastarg$ at you", 
      "$mcname$ glares $lastarg$ at $hcname$", }) }),
  "greet" : ({ ({ 0, "%s" }), ({
      "You greet $hcname$ $arg:happily,sadly,with open arms,"+
      "ecstaticly,carefully,courteously,hysterically,"+
      "reservedly,warmly,coldly,insolently,curtly,"+
      "absentmindedly$",
      "$mcname$ greets you $lastarg$",
      "$mcname$ greets $hcname$ $lastarg$", }) }),
  "grimace" : ({ ({ 3, "%s" }), ({
      "You grimace in $arg:disgust,anger,thought,power,despair$",
      "$mcname$ grimaces in $lastarg$", }), }),
  "grin" : ({ ({ 0, "%s", 0, "at %s", 1, "%s at %s", 2, "at %s %s",
      1, "%s %s", 2, "%s %s", 3, "%s" }), ({
      "You grin$ifarg: $arg:manically,evilly,wickedly,insanely,mischievously,"+
      "impishly,cheekily,idiotically,tentatively,"+
      "like a duck with a flexible beak$~$",
      "$mcname$ grins$ifarg: $lastarg$~$",
      "You grin$ifarg: $arg:manically,evilly,wickedly,insanely,mischievously,"+
      "impishly,cheekily,idiotically,"+
      "like a duck with a flexible beak$~$ at $hcname$",
      "$mcname$ grins$ifarg: $lastarg$~$ at you",
      "$mcname$ grins$ifarg: $lastarg$~$ at $hcname$" }) }),
  "grind" : ({ ({ 3, "%s" }), ({
      "You grind your teeth $arg:noisily,seductively,in terror,together,"+
      "annoyingly,suggestively,painfully,angrily$",
      "$mcname$ grinds $mposs$ teeth $lastarg$", }) }),
  "groan" : ({ ({ 3, "%s" }), ({
      "You groan$ifarg: $arg:loudly,resignedly,tiredly$~$",
      "$mcname$ groans$ifarg: $lastarg$~$" }) }),
  "grope" : ({ ({ 0, "%s", 1, "%s %s" }), ({
      "You grope $ifarg:$mhcname$ $arg:#$$else$$hcname$~$",
      "$mcname$ gropes you$ifarg: $lastarg$~$",
      "$mcname$ gropes $ifarg:$mhcname$ $lastarg$$else$$hcname$~$" }) }),
  "grovel" : ({ ({ 0, "%s", 0, "at %s", 1, "%s %s", 1, "%s at %s", 3, "%s", 2, "at %s %s", }),
    ({
      "You grovel$ifarg: $arg:shamelessly,violently,unashamedly$~$",
      "$mcname$ grovels$ifarg: $lastarg$~$",
      "You grovel$ifarg: $arg:shamelessly,violently,unashamedly$~$ at"+
      " $mhcname$ feet",
      "$mcname$ grovels$ifarg: $lastarg$~$ at your feet",
      "$mcname$ grovels$ifarg: $lastarg$~$ at $mhcname$ feet" }) }),
  "growl" : ({ ({
      0, "%s", 0, "at %s", 1, "%s %s", 1, "%s at %s",
      2, "at %s %s", 2, "%s %s", 3, "%s" }), ({
      "You growl $arg:menacingly,nastily,loudly,playfully$",
      "$mcname$ growls $lastarg$",
      "You growl $arg:menacingly,nastily,loudly,playfully$ at $hcname$",
      "$mcname$ growls $lastarg$ at you",
      "$mcname$ growls $lastarg$ at $hcname$" }) }),
  "grumble" : ({ ({ 3, "%s", }), ({
      "You grumble $arg:quietly,bitterly,menacingly,halfheartedly,"+
      "seductively,suggestively,loudly,annoyingly,devastatingly,carefully,"+
      "wildly,more or less$",
      "$mcname$ grumbles $lastarg$", }) }),
  "gurgle" : ({ ({ 3, "%s" }), ({
      "You gurgle $arg:noisily,rudely,loudly,mischievously,"+
      "happily,carefully,disgustingly,in surprise,"+
      "like a train,quickly,slowly$",
      "$mcname$ gurgles $lastarg$" }) }),
  "hang" : ({ ({ 3, "%s", }), ({
      "You hang your head in $arg:shame,sorrow,despair,happiness$",
      "$mcname$ hangs $mposs$ head in $lastarg$", }) }),
  "headbutt" : ({ ({ 0, "%s"}), ({
      "You head butt $hcname$", "$mcname$ headbutts you",
      "$mcname$ headbutts $hcname$" }) }),
  "headstand" : ({ ({ 0, "on %s", 0, "%s" }), ({
      "You stand on your head", "$mcname$ stands on $mposs$ head",
      "You stand on $mhcname$ head", "$mcname$ stands on your head",
      "$mcname$ stands on $mhcname$ head" }) }),
  "hiccup" : ({ 0, ({ /* exciting stuff */
      "You hiccup",
      "$mcname$ hiccups" }) }),
  "high5" : ({ ({ 0, "%s" }), ({
      "Nope",
      "$mcname$ is stupid, isn't $mpronoun$?",
      "Nope, sorry.  Absolutely not",
      "Ignore $mcname$, $mpronoun$'s actually pretty stupid",
      "Ignore $mcname$, $mpronoun$'s actually pretty stupid" }) }),
  "hop" : ({ 0, ({ "You hop around a bit", "$mcname$ hops around a bit" }) }),
  "hoot" : ({ ({ 3, "%s" }), ({
      "You hoot $arg:like Owls,derisively,annoyingly,absentmindedly,"+
      "whilst you work,distractedly,pointlessly,silently,loudly,"+
      "rudely,with laughter,vaguely,obviously,tunelessly$",
      "$mcname$ hoots $lastarg$" }), }),
  "howl" : ({ ({ 3, "%s", 3, "at the %s" }), ({
      "HOOOOOWWWWWWWWWLLLLLL!!",
      "$mcname$ howls$ifarg: $arg:at the moon,at the #$~$" }) }),

  "hug" : ({ ({ 0, "%s", 1, "%s %s", 2, "%s %s" }), ({
      "You hug $hcname$$ifarg: $arg:tightly,warmly,gently,close$~$",
      "$mcname$ hugs you$ifarg: $lastarg$~$",
      "$mcname$ hugs $hcname$$ifarg: $lastarg$~$" }) }),
  "hum" : ({ ({ 3, "%s" }), ({
      "You hum $arg:a merry tune,tunelessly,annoyingly,vaguely,absentmindedly,"+
      "whilst you work,distractedly,pointlessly,silently,loudly,"+
      "rudely$",
      "$mcname$ hums $lastarg$" }), }),
  "idle" : ({ ({ 0, "%s", 3, "%s" }), ({
      "You idle $arg:like pinkfish,like ducky,like biggles,like sloths do,"+
      "like a gherkin,like everyone else is,nonchalantly,quickly,"+
      "unbelievably well,without using your hands,upside-down,"+
      "hyperactively,standing still,artfully,around,intensely,like bastian$",
      "$mcname$ idles $lastarg$",
      "You idle like $hcname$",
      "$mcname$ idles like you",
      "$mcname$ idles like $hcname$", }), }),
  "ignore" : ({ ({ 0, "%s" }), ({
      "You ignore the world",
      "$mcname$ ignores the world",
      "You ignore $hcname$",
      "$mcname$ ignores you",
      "$mcname$ ignores $hcname$", }) }),
  "james" : ({ 0, ({
      "Ow! I feel good! da na da na da na da! I knew that I would!",
      "$mcname$ feels good, da na da na da na da!" }) }),
  "juggle" : ({ ({ 3, "%s" }), ({
      "You juggle some $arg:balls,sticks,batons,cats,dogs,frogs,chickens,"+
      "swords,knives,arms,legs,balls,trees,chain saws,bottles,"+
      "guppies,torches,bings,tree stumps,logs,zoroasters,"+
      "wine glasses,water,people,fire,ladies,men,rhinos$ around",
      "$mcname$ juggles some $lastarg$ around", }) }),
  "jump" : ({ ({ 0, "on %s", 0, "%s", 2, "on %s %s",
      1, "%s on %s", 1, "%s %s", 2, "%s %s", 3, "%s" }), ({
      "You jump up and down $arg:excitedly,happily,carefully,slowly,"+
      "joyfully,unsteadily,ecstaticly,worriedly,sideways,"+
      "absentmindedly,like pinkfish,like a prancing piranha$",
      "$mcname$ jumps up and down $lastarg$",
      "You jump up and down on $hcname$$ifarg: $arg:"+
      "excitedly,happily,carefully,slowly,"+
      "joyfully,unsteadily,ecstaticly,worriedly,sideways,"+
      "absentmindedly,like pinkfish$~$",
      "$mcname$ jumps up and down on you$ifarg: $lastarg$~$",
      "$mcname$ jumps up and down on $hcname$$ifarg: $lastarg$~$" }) }),
  "kick" : ({ ({ 0, "%s", 1, "%s %s", 2, "%s %s", 3, "%s" }), ({
      "You kick yourself$ifarg: $arg:#$~$",
      "$mcname$ kicks $mobj$self",
      "You kick $hcname$$ifarg: $arg:#$~$",
      "$mcname$ kicks you$ifarg: $lastarg$~$",
      "$mcname$ kicks $hcname$$ifarg: $lastarg$~$" }) }),
  "kiss" : ({ ({ 0, "%s", 1, "%s %s", 2, "%s %s" }), ({
      "You kiss $hcname$$ifarg: $arg:passionately,deeply,tenderly,gently,"+
      "lovingly,lengthily,fishily,carefully,demandingly,sensuously$~$",
      "$mcname$ kisses you$ifarg: $lastarg$~$",
      "$mcname$ kisses $hcname$$ifarg: $lastarg$~$" }) }),
  "knee" : ({ ({ 0, "%s", 1, "%s %s" }), ({
      "You knee $hcname$$ifarg: $arg:#$~$",
      "$mcname$ knees you$ifarg: $lastarg$~$",
      "$mcname$ knees $hcname$$ifarg: $lastarg$~$" }) }),
  "laugh" : ({ ({
      0, "at %s", 0, "%s", 1, "%s %s", 1, "%s at %s",
      2, "at %s %s", 3, "%s"}), ({
      "$ifarg:You laugh $arg:nastily,nicely,quietly,uncontrollably,politely,"+
      "happily,manically,ecstaticly,demonically$"+
      "$else$You fall down laughing~$",
      "$ifarg:$mcname$ laughs $lastarg$$else$$mcname$ falls down laughing~$",
      "You laugh$ifarg: $arg:nastily,nicely,quietly,uncontrollably,politely,"+
      "happily,manically,ecstaticly,demonically$~$"+
      " at $hcname$",
      "$mcname$ laughs$ifarg: $lastarg$~$ at you",
      "$mcname$ laughs$ifarg: $lastarg$~$ at $hcname$" }) }),
  "leap" : ({ ({ 3, "%s" }), ({
      "You leap$ifarg: $arg:longingly,excitedly,quickly,slowly,awkwardly,"+
      "politely,quietly,noisily$~$ into the air",
      "$mcname$ leaps$ifarg: $lastarg$~$ into the air", }) }),
  "leer" : ({ ({ 0, "%s", 0, "at %s" }), ({
      "You leer at yourself",
      "$mcname$ leers at $mobj$self, hmm interesting",
      "You leer at $hcname$",
      "$mcname$ leers at you",
      "$mcname$ leers at $hcname$", }), }),
  "lick" : ({ ({ 0, "%s" }), ({
      "You lick your lips",
      "$mcname$ licks $mposs$ lips",
      "You lick $hcname$",
      "$mcname$ licks you",
      "$mcname$ licks $hcname$" }) }),
  "loom" : ({ ({ 0, "%s", 0, "over %s" }), ({
      "You loom over $hcname$",
      "$mcname$ looms over you",
      "$mcname$ looms over $hcname$", }) }),
  "love" : ({ ({ 0, "%s" }), ({
      "You whisper sweet nothings into $mhcname$ ear",
      "$mcname$ whispers sweet nothings in your ear",
      "$mcname$ whispers to $hcname$" }) }),
  "lower" : ({ 0, ({
      "You lower your eyebrows",
      "$mcname$ lowers $mposs$ eyebrows", }) }),
  "massage" : ({ ({ 0, "%s", 2, "%s %s", }), ({
      "You give $hcname$ a$ifarg: $arg:good,bad,ugly,long,"+
      "refreshing,pink,full body,seductive,sensuous,strange,"+
      "painful,deep,meaningful,ergonomic,economic,"+
      "painless,memorable,different,unwanted,unwarranted,"+
      "unprovoked,unknown,sneaky,unnoticed,unwieldy,back,"+
      "professional,unprofessional,happy,sad,trained,untrained,"+
      "train,virgin mary,compact,quick,foot,leg,arm,head,teeth,"+
      "ear,neck,shoulder,nose$~$ massage",
      "$mcname$ gives you a$ifarg: $lastarg$~$ massage",
      "$mcname$ gives $hcname$ a$ifarg: $lastarg$~$ massage", }) }),
  "moan" : ({ ({ 3, "%s" }), ({
      "You moan$ifarg: $arg:gently,deeply,sensually,agonizingly,in terror$~$",
      "$mcname$ moans$ifarg: $lastarg$~$" }) }),
  "moo" : ({ 0, ({
      "Moooooooooooooo",
      "$mcname$ bites the dust (Moooooooooo)" }) }),
  "moon" : ({ 0, ({
      "You drop your pants and moon $hcname$",
      "$mcname$ drops $mposs$ pants and moons you",
      "$mcname$ drops $mposs$ pants and moons $hcname$", }), }),
  "mosh" : ({ 0, ({
      "You mosh $arg:violently,angrily,carefully,thoughtfully,"+
      "wonderingly,vigously,insanely,loudly$ around the room",
      "$mcname$ moshes $lastarg$ around the room", }) }),
  "mutter" : ({ ({ 3, "%s" }), ({
      "You $ifarg:mutter $arg:#$ under your breath$else$mutter under "+
      "your breath~$",
      "$mcname$ mutters $ifarg:$arg:#$ under ~$$mposs$ breath", }) }),
  "nestle" : ({ ({ 0, "%s", }), ({
      "You nestle up to $hcname$ $arg:affectionately,lovingly,curiously$",
      "$mcname$ nestle up to you $lastarg$",
      "$mcname$ nestle up to $hcname$ $lastarg$", }) }),
  "nibble" : ({ ({ 0, "%s", 1, "%s %s", 2, "%s %s" }), ({
      "You nibble on $mhcname$ $arg:ear,finger,lip,arm,leg,toe,nose$",
      "$mcname$ nibbles on your $lastarg$",
      "$mcname$ nibbles on $mhcname$ $lastarg$" }) }),
  "nod" : ({ ({
      0, "%s", 1, "%s at %s", 1, "%s %s", 2, "at %s %s",
      2, "%s %s", 3, "%s" }), ({
      "You nod $arg:solemnly,happily,brightly,curtly,patiently,slowly,"+
      "knowingly,vigorously,in agreement,in disagreement,tentatively$",
      "$mcname$ nods $lastarg$",
      "You nod $arg:solemnly,happily,brightly,curtly,patiently,slowly,"+
      "knowingly,vigorously$"+
      " at $hcname$",
      "$mcname$ nods $lastarg$ at you",
      "$mcname$ nods $lastarg$ at $hcname$", }) }),
  "noise" : ({ ({ 3, "%s" }), ({
      "$ifarg:You make a $arg:bungle,flurgle,zongle-wop,wop,whirr,burble,frog,"+
      "moo,train,hairy,twisted,wap,pop,schwing,gong,koala,duck,quacking,"+
      "rat,mouse,chicken,womble,guppy,cow,rabbit,kangaroo,gumby$ noise"+
      "$else$You make a funny noise~$",
      "$ifarg:$mcname$ makes a $lastarg$ noise$else$$mcname$ makes a funny noise~$" }) }),
  "nudge" : ({ ({ 0, "%s", }), ({
      "You nudge $hcname$",
      "$mcname$ nudges you",
      "$mcname$ nudges $hcname$", }) }),
  "nuzzle" : ({ ({ 0, "%s" }), ({
      "You nuzzle $hcname$ affectionately",
      "$mcname$ nuzzles you affectionately",
      "$mcname$ nuzzles $hcname$ affectionately", }), }),
  "raise" : ({ 0, ({ "You raise your eyebrows", "$mcname$ raises $mposs$ eyebrows" }) }),
  "razz" : ({ ({ 0, "%s" }), ({
      "You stick your thumb on your nose and razz $hcname$",
      "$mcname$ sticks $mposs$ thumb on $mposs$ nose and razz's you",
      "$mcname$ sticks $mposs$ thumb on $mposs$ nose and razz's $hcname$" }) }),
  "rub" : ({ ({ 0, "%s", 3, "%s" }), ({
      "You rub your $arg:hands together,eyes,tummy,nose,leg,arm,eyebrows,head$",
      "$mcname$ rubs $mposs$ $lastarg$",
      "You rub $hcname$ up the wrong way",
      "$mcname$ rubs you up the wrong way",
      "$mcname$ rubs $hcname$ up the wrong way", }) }),
  "panic" : ({ 0, ({
      "You panic",
      "$mcname$ panics", }) }),
  "pat" : ({ ({ 0, "%s", 2, "%s on the %s", 2, "%s on %s", 1, "%s %s", 2, "%s %s" }), ({
      "You pat $hcname$ on the $arg:head,back,leg,arm,nose,bottom$",
      "$mcname$ pats you on the $lastarg$",
      "$mcname$ pats $hcname$ on the $lastarg$" }) }),
  "pet" : ({ ({ 0, "%s" }), ({
      "You pet Goldie",
      "$mcname$ pets Goldie",
      "You pet $hcname$",
      "$mcname$ pets you",
      "$mcname$ pets $hcname$", }) }),
  "peer" : ({ ({
      0, "%s", 0, "at %s", 1, "%s at %s", 1, "%s %s", 2, "at %s %s",
      2, "%s %s", 3, "%s" }), ({
      "You peer$ifarg: $arg:suspiciously,quizzically,"+
      "anxiously,stupidly,warningly,expectantly,happily,sadly,desperately,"+
      "worriedly,strangely,uncertainly,lopsidedly,lazily,rudely,disappointedly,"+
      "fishily,fearfully,like a train,curiously,tentatively,"+
      "warily,nervously,carefully,warningly,owlishly,dazedly$~$ around the room",
      "$mcname$ peers$ifarg: $lastarg$ around the room~$",
      "You peer$ifarg: $arg:suspiciously,quizzically,warily,nervously,"+
      "anxiously,stupidly,warningly,expectantly,happily,sadly,desperately,"+
      "worriedly,strangely,uncertainly,lopsidedly,lazily,rudely,disappointedly,"+
      "fishily,fearfully,like a train,curiously,"+
      "carefully,warningly,intently,owlishly,dazedly$~$ at $hcname$",
      "$mcname$ peers$ifarg: $lastarg$~$ at you",
      "$mcname$ peers$ifarg: $lastarg$~$ at $hcname$", }) }),
  "pick" : ({ ({ 3, "%s" }), ({ 
      "You pick your $arg:nose,ear,#$",
      "$mcname$ picks $mposs$ $lastarg$" }) }),
  "pinch" : ({ ({ 0, "%s", 2, "%s on %s", 2, "%s on the %s", 1, "%s %s", 2, "%s %s" }),({
      "You pinch yourself",
      "$mcname$ pinches $mobj$self",
      "You pinch $hcname$$ifarg: on the $arg:bottom,leg,arm,frog,cheek$~$",
      "$mcname$ pinches you$ifarg: on the $lastarg$~$",
      "$mcname$ pinches $hcname$$ifarg: on the $lastarg$~$",}) }),
  "ping" : ({ ({ 0, "%s" }), ({
      "You ping $hcname$", "$mcname$ pings you$force#ack $mname$#2$",
      "$mcname$ pings $hcname$" })  }),
  "plead" : ({ ({ 3, "%s", }), ({
      "$mcname$ pleads for $arg:mercy,frogs,lots of money,a Decstation 5000,"+
      "this stupid soul to go away,an X windows terminal,insanity,"+
      "creators,bil,pinkfish's sanity$",
      "$mcname$ pleads for $lastarg$", }) }),
  "point" : ({ ({ 0, "%s", 0, "at %s", 1, "%s at %s", 2, "at %s %s" }), ({
      "You point$ifarg: $arg:accusingly,straight$~$ at $hcname$",
      "$mcname$ points$ifarg: $lastarg$~$ at you",
      "$mcname$ points$ifarg: $lastarg$~$ at $hcname$" }) }),
  "poke" : ({ ({ 0, "%s", 2, "%s in the %s", 2, "%s in %s", 2, "%s %s", 1, "%s %s" }), ({
      "You poke $hcname$$ifarg: in the $arg:eyes,ribs,legs,nose,ear,"+
      "stomach,#$~$",
      "$mcname$ pokes you$ifarg: in the $arg:eyes,ribs,legs,nose,ear,"+
      "stomach,#$~$",
      "$mcname$ pokes $hcname$$ifarg: in the $arg:eyes,ribs,legs,nose,ear,"+
      "stomach,#$~$"}) }),
  "ponder" : ({ 0, ({
      "You ponder the situation",
      "$mcname$ ponders the situation" }) }),
  "pout" : ({ ({ 3, "%s" }), ({
      "You pout$ifarg: $arg:childishly,silently,resignedly$~$",
      "$mcname$ pouts$ifarg: $lastarg$~$" }) }),
  "protest" : ({ ({ 3, "%s" }), ({
      "You protest$ifarg: $arg:vehemently,loudly,strongly,weakly,"+
      "against duck-shooting,noisily,pointlessly,annoyingly,#$~$",
      "$mcname$ protests$ifarg: $lastarg$~$" }) }),
  "puke" : ({ ({ 0, "on %s", 0, "%s", 0, "at %s"  }), ({
      "You brighten up the place", "$mcname$ does a technicolor yawn",
      "You puke on $hcname$", "$mcname$ pukes on you",
      "$mcname$ pukes on $hcname$" }) }),
  "punch" : ({ ({ 0, "%s" }), ({
      "You punch yourself",
      "$mcname$ punches $mobj$self",
      "You punch $hcname$",
      "$mcname$ punches You",
      "$mcname$ punches $hcname$", }) }),
  "purr" : ({ ({ 3, "%s" }), ({
      "You purr $arg:contentedly,loudly,happily,sensuously$",
      "$mcname$ purrs $lastarg$" }) }),
  "push" : ({ ({ 0, "%s", }), ({
      "You push yourself over",
      "$mcname$ pushes $mobj$self over",
      "You push $hcname$ over",
      "$mcname$ pushes you over",
      "$mcname$ pushes $hcname$ over", }) }),
  "puzzle" : ({ ({ 3, "%s" }), ({
      "$ifarg:You puzzle over $arg:#$$else$You look puzzled~$",
      "$mcname$ $ifarg:puzzles over $lastarg$$else$looks puzzled~$", }) }),
  "quirk" : ({ 0, ({
      "You quirk one eyebrow",
      "$mcname$ quirks one eyebrow" }) }),
  "quiver" : ({ 0, ({
      "You quiver",
      "$mcname$ quivers" }), }),
  "ram" : ({ ({0 ,"%s", 1, "%s %s", 2, "%s %s", 3, "%s"}), ({
      "$ifarg:You ram the $arg:#$$else$You ram the nearest turtle~$",
      "$mcname$ $ifarg:rams the $lastarg$$else$rams the nearest "+
      "turtle. <thwok>~$",
      "You ram $ifarg:$mhcname$ $arg:#$$else$$arg:#$~$",
      "$mcname$ $ifarg:rams into your $arg:#$$else$rams into you~$",
      "$mcname$ $ifarg:rams into $mhcname$ $arg:#$$else$rams into $hcname$~$"
    }), }),

  "roll" : ({ ({ 2, "%s %s", 1, "%s %s", 3, "%s", 0, "%s" }), ({
      "You roll $arg:your eyes,around on the floor laughing,"+
      "over and play dead,up into a ball,your own cigarette,"+
      "sideways,backwards,professionally,like a spy through an "+
      "imaginary door,fearfully,tightly,slowly$",
      "$mcname$ rolls $lastarg$",
      "You roll $ifarg:$arg:quickly,slowly,painfully,excitededly,lovingly,"+
      "carefully$ ~$over $hcname$",
      "$mcname$ rolls $ifarg:$lastarg$ ~$over you",
      "$mcname$ rolls $ifarg:$lastarg$ ~$over $hcname$" }) }),
  "ruffle" : ({ ({ 0, "%s", 2, "%s %s", 1, "%s %s" }), ({
      "You ruffle $mhcname$ hair$ifarg: $arg:playfully,affectionately$~$",
      "$mcname$ ruffles your hair$ifarg: $lastarg$~$",
      "$mcname$ ruffles $mhcname$ hair$ifarg: $lastarg$~$" }) }),
  "scratch" : ({ ({0, "%s", 1, "%s %s", 2, "%s %s" }), ({
      "You scratch your head",
      "$mcname$ scratches $mposs$ head",
      "$ifarg:You $arg:viciously,slightly,wombely$ scratch $mhcname$ "+
      "head$else$You scratch $hcname$~$",
      "$ifarg:$mcname$ $lastarg$ scratches your head$else$"+
      "$mcname$ $lastarg$ scratches you~$",
      "$mcname$ $ifarg:$lastarg$ ~$scratches $mhcname$ head"
    }) }),
  "scream" : ({ ({ 3, "%s", 3, "in %s" }), ({
      "$ifarg:You scream in $arg:terror,fright,fear,pain,surprise,frustration,"+
      "despair,anger$$else$Arrggghhhhh!!!!~$",
      "$mcname$ screams$ifarg: in $lastarg$$else$ loudly~$" }) }),
  "scowl" : ({ ({ 0, "%s" }), ({
      "You scowl", 
      "$mcname$ scowls",
      "You scowl at $hcname$",
      "$mcname$ scowls at you",
      "$mcname$ scowls at $hcname$" }) }),
  "schlop" : ({ ({ 0, "%s" }), ({
      "You schlop",
      "$mcname$ schlops",
      "You schlop $hcname$",
      "$mcname$ schlops you",
      "$mcname$ schlops  $hcname$" }) }),
  "shake" : ({ ({ 0, "%s", 1, "%s with %s", 1, "%s %s", 1, "%s %s", 3, "%s",
      1, "%s at %s", 3, "my %s", }), ({
      "You shake your head$ifarg: $arg:sorrowfully,carefully,slowly,"+
      "once,quickly,curtly,in disagreement,vigously,completely,fishily,"+
      "tentatively,in agreement,in disbelief$~$",
      "$mcname$ shakes $mposs$ head$ifarg: $lastarg$~$",
      "You shake$ifarg: $arg:hands with,flippers with,fingers with,legs with,"+
      "wings with,tentacles with,your fist at$~$ $hcname$",
      "$mcname$ shakes$ifarg: $lastarg$~$ you",
      "$mcname$ shakes$ifarg: $lastarg$~$ $hcname$" }) }),
  "shiver" : ({ ({ 3, "with %s", 3, "in %s" }), ({
      "You shiver$ifarg: $arg:fear,with cold,slightly,#$~$",
      "$mcname$ shivers$ifarg: $lastarg$~$" }) }),
  "shrug" : ({ 0, ({ "You shrug", "$mcname$ shrugs", }) }),
  "shudder" : ({ ({ 3, "%s" }), ({
      "You shudder $ifarg:in $arg:fear,revulsion,disappointment,ecstasy"+
      "$$else$from horror~$",
      "$mcname$ shudders $ifarg:in $lastarg$$else$from horror~$", }) }),
  "sigh" : ({ ({ 3, "%s" }), ({
      "You sigh$ifarg: $arg:deeply,silently,desperately,tiredly,sadly,slowly,"+
      "dreamily,happily,"+
      "heavily,suggestively,sarcasticly,in relief,with relief$~$",
      "$mcname$ sighs$ifarg: $lastarg$~$" }) }),
  "sing" : ({ ({ 0, "%s", 3, "%s" }), ({
      "You sing $arg:in appreciation of life,#$",
      "$mcname$ $ifarg:sings $lastarg$$else$bursts out into song~$",
      "You serenade $hcname$",
      "$mcname$ serenades you",
      "$mcname$ serenades $hcname$" }) }),
  "sit" : ({ 0, ({
      "You sit down",
      "$mcname$ sits down", }) }),

  "slap" : ({ ({ 0, "%s" }), ({
      "You slap your forehead",
      "$mcname$ slaps $mposs$ forehead",
      "You slap $hcname$", "$mcname$ slaps you",
      "$mcname$ slaps $hcname$" }) }),
  "sleep" : ({ ({ 0, "%s" }), ({
      "You go to sleep",
      "$mcname$ goes to sleep",
      "You go to sleep in $mhcname$ arms",
      "$mcname$ go to sleep in your arms",
      "$mcname$ goes to sleep in $mhcname$ arms", }) }),
  "smooch" : ({ ({ 0, "%s", 1, "%s %s", 2, "%s %s" }), ({
      "You smooch $hcname$ $arg:lovingly,effectively,demandingly,wantingly,until eternity,affectionately,warmly,gently$",
      "$mcname$ smooches you $lastarg$",
      "$mcname$ smooches $hcname$ $lastarg$" }) }),
  "smirk" : ({ 0, ({ "You smirk", "$mcname$ smirks" }) }),
  "smile" : ({ ({
      0, "at %s", 0, "%s", 1, "%s at %s", 1, "%s %s", 2, "at %s %s",
      2, "%s %s", 3, "%s", }), ({
      "You smile$ifarg: $arg:happily,sadly,nervously,wryly,broadly,crookedly,"+
      "stupidly,idiotically,condescendingly,ironically,patiently,brightly,"+
      "slightly,nastily,excitedly,strangely,with forced patience,plasticly,"+
      "carefully,sadisticly,lopsidedly,fishily,catishly,faintly,"+
      "like a train,angrily,paranoicaly,innocently,frogily,slyly,"+
      "weakly,humbly,paradoxically,sarcasticly,viciously,garishly,"+
      "sweetly,innocently,lovingly,dreamily,radiantly,enthusiasticly,"+
      "insolently,quirkily,completely,unconsciously,drunkenly,"+
      "insanely,cutely,maliciously,"+
      "absentmindedly,curtly,disturbingly,unbelievably,quietly,"+
      "loudly,differently,winningly,in triumph,seductively,"+
      "tightly,gosh there are lots of arguments,softly,"+
      "lividly,demonically,warmly,"+
      "manically,warily,sardonically,lazily,serenely,disappointedly$~$",
      "$mcname$ smiles$ifarg: $lastarg$~$",
      "You smile$ifarg: $arg:happily,sadly,nervously,wryly,broadly,crookedly,"+
      "stupidly,idiotically,condescendingly,ironically,patiently,brightly,"+
      "slightly,nastily,excitedly,strangely,with forced patience,plasticly,"+
      "manically,carefully,sadisticly,lopsidedly,fishily,catishly,faintly,"+
      "weakly,humbly,paradoxically,sarcasticly,viciously,garishly,"+
      "insolently,quirkily,completely,unconsciously,drunkenly,"+
      "absentmindedly,curtly,disturbingly,unbelievably,quietly,"+
      "loudly,differently,winningly,in triumph,seductively,"+
      "sweetly,innocently,lovingly,dreamily,radiantly,enthusiasticly,"+
      "like a train,angrily,paranoicaly,innocently,frogily,slyly,"+
      "macabrely,ruefully,tentatively,like a dog,"+
      "tightly,gosh there are lots of arguments,softly,"+
      "insanely,cutely,maliciously,"+
      "lividly,demonicaly,"+
      "sardonically,warily,lazily,serenely,disappointedly$~$ at $hcname$",
      "$mcname$ smiles$ifarg: $lastarg$~$ at you",
      "$mcname$ smiles$ifarg: $lastarg$~$ at $hcname$" }) }),
  "snap" : ({ ({ 0, "%s", 1, "%s at %s", 1, "my %s at %s", 3, "%s" }), ({
      "You snap your $arg:fingers,leg,arm in a quick salute$",
      "$mcname$ snaps $mposs$ $lastarg$",
      "You snap your $arg:fingers,leg,arm in a quick salute$ at $hcname$",
      "$mcname$ snaps $mposs$ $lastarg$ at you",
      "$mcname$ snaps $mposs$ $lastarg$ at $hcname$" }) }),
  "snarl" : ({ ({ 0, "%s", 1, "%s at %s", 1, "%s %s", 2, "at %s %s" }), ({
      "You snarl $arg:viciously,nastily,demonicaly,happily,sadly,"+
      "unexpectedly,suddenly$ at $hcname$",
      "$mcname$ snarls $lastarg$ at you",
      "$mcname$ snarls $lastarg$ at $hcname$", }) }),
  "sneer" : ({ ({ 0, "%s" }), ({
      "You sneer at $hcname$",
      "$mcname$ sneers at you",
      "$mcname$ sneers at $hcname$", }) }),
  "sneeze" : ({ ({ 0, "at %s", 2, "%s at %s", 3, "%s" }), ({
      "You sneeze $arg:violently,loudly,silently,quietly,suddenly,unexpectedly$",
      "$mcname$ sneezes $lastarg$",
      "You sneeze $arg:violently,loudly,silently,quietly,suddenly,unexpectedly$"+
      " at $hcname$",
      "$mcname$ sneezes $lastarg$ at you",
      "$mcname$ sneezes $lastarg$ at $hcname$" }) }),
  "snicker" : ({ ({ 3, "%s" }), ({
      "You snicker$ifarg: $arg:mischievously,nastily,a bit,like skippy$~$",
      "$mcname$ snickers$ifarg: $lastarg$~$" }) }),
  "sniff" : ({ ({ 3, "%s" }), ({
      "You sniff$ifarg: $arg:dejectedly,noisily,silently,loudly,in disdain$~$",
      "$mcname$ sniffs$ifarg: $lastarg$~$" }) }),
  "snigger" : ({ 0, ({
      "You snigger",
      "$mcname$ sniggers", }) }),
  "snore" : ({ 0, ({
      "You snore loudly",
      "$mcname$ snores loudly" }) }),
  "snort" : ({ 0, ({
      "You snort",
      "$mcname$ snorts", }) }),
  "snuggle" : ({ ({ 0, "%s", 1, "%s %s", 2, "%s %s" }), ({
      "You snuggle up to $hcname$ $arg:affectionately,warmly,gently$",
      "$mcname$ snuggles up to you $lastarg$",
      "$mcname$ snuggles up to $hcname$ $lastarg$" }) }),
  "sob" : ({ ({ 0, "%s", 3, "%s",  0, "on %s" }), ({
      "You sob $arg:quietly,loudly,despairingly,forlornly,happily,"+
      "completely,unexpectedly,silently,cheekily$",
      "$mcname$ sobs $lastarg$",
      "You sob on $mhcname$ shoulder",
      "$mcname$ sobs on your shoulder",
      "$mcname$ sobs on $mhcname$ shoulder", }) }),
  "sorry" : ({ ({ 0, "%s", 1, "%s %s", 2, "%s %s", }), ({
      "You apologize$ifarg: $arg:profusely,reservedly,profunctily,"+
      "carefully,insultingly,insolently$~$ to $hcname$",
      "$mcname$ apologizes$ifarg: $lastarg$~$ to you",
      "$mcname$ apologizes$ifarg: $lastarg$~$ to $hcname$", }) }),
  "spank" : ({ ({ 0, "%s", 2, "%s %s" }), ({
      "You spank $hcname$$ifarg: $arg:seductively,carefully,gently,"+
      "uncontrollably,politely,sensuously,selectively,unexpectedly,"+
      "with an evil smirk,painfully,sneakily,unprovoked,professionally,vigorously,"+
      "reflexively,with a cat,like a train,like a virgin mary,"+
      "with a virgin mary$~$",
      "$mcname$ spanks you$ifarg: $lastarg$~$",
      "$mcname$ spanks $hcname$$ifarg: $lastarg$~$", }) }),
  "spit" : ({ ({ 0, "%s", 0, "at %s" }), ({
      "You spit.",
      "$mcname$ spits.",
      "You spit in $mhcname$ face",
      "$mcname$ spits in your face",
      "$mcname$ spits in $mhcname$ face" }) }),
  "spock" : ({ 0, ({
      "You raise one eyebrow",
      "$mcname$ raises one eyebrow", }) }),
  "squeeze" : ({ ({ 0, "%s", 1, "%s %s", 2, "%s %s" }), ({
      "You squeeze $hcname$ $arg:fondly,gently,tightly$",
      "$mcname$ squeezes you $lastarg$",
      "$mcname$ squeezes $hcname$ $lastarg$" }) }),
  "stagger" : ({ ({ 3, "%s" }), ({
      "You stagger around$ifarg: $arg:#$~$",
      "$mcname$ staggers around$ifarg: $lastarg$~$" }) }),
  "stamp" : ({ ({ 3, "%s", }), ({
      "You stamp your foot$ifarg: $arg:angrily,impatiently,warningly,"+
      "frighteningly$~$",
      "$mcname$ stamps $mposs$ foot$ifarg: $lastarg$~$" }) }),
  "stand" : ({ ({ 3, "%s", }), ({
      "You stand $arg:in uffish thought,about,patiently$",
      "$mcname$ stands $lastarg$" }) }),
  "stare" : ({ ({ 0, "%s", 1, "%s %s", 1, "%s at %s", 3, "%s" }), ({
      "You stare$ifarg: $arg:happily,sadly,worriedly,lazily,rudely,dazedly,"+
      "hungrily,macabrely,absent-mindedly,fanatically,lovingly,"+
      "respectfully,womblely,frogily,desperately,sternly,"+
      "tentatively,politely,listlessly,"+
      "dreamily,intently,mindlessly,expectantly,longingly$~$ into space",
      "$mcname$ stares$ifarg: $lastarg$~$ into space",
      "You stare$ifarg: $arg:happily,sadly,worriedly,lazily,rudely,dazedly,"+
      "hungrily,macabrely,absent-mindedly,fanatically,lovingly,"+
      "respectfully,womblely,frogily,desperately,sternly,"+
      "tentatively,politely,listlessly,"+
      "dreamily,intently,mindlessly,romantically,expectantly,longingly,"+
      "continuously,annoyingly$~$ at $hcname$",
      "$mcname$ stares$ifarg: $lastarg$~$ at you",
      "$mcname$ stares$ifarg: $lastarg$~$ at $hcname$" }) }),
  "stifle" : ({ 0, ({
      "You stifle a giggle",
      "$mcname$ stifles a giggle", }) }),
  "strangle" : ({ ({ 0, "%s", 1, "%s about %s", 1, "%s %s" }), ({
      "You strangle yourself",
      "$mcname$ strangles $mobj$self",
      "You strangle $hcname$$ifarg: about $arg:#$~$",
      "$mcname$ strangles you$ifarg: about $arg:#$~$",
      "$hcname$ strangles $mcname$$ifarg: about $arg:#$~$", }) }),
  "stroke" : ({ ({ 0, "%s" }), ({
      "You stroke $hcname$",
      "$mcname$ strokes you",
      "$mcname$ strokes $hcname$", }) }),
  "strut" : ({ 0, ({
      "You strut your stuff",
      "$mcname$ struts proudly around the room" }) }),
  "stumble" : ({ ({ 3, "%s" }), ({
      "You stumble $ifarg:$arg:#$$else$around the room~$",
      "$mcname$ stumbles $ifarg:$arg:#$$else$around the room~$" }) }),
  "suck" : ({ ({ 3, "%s" }), ({ 
      "You suck your $arg:thumb,pen,#$",
      "$mcname$ sucks $mposs$ $lastarg$" }) }),
  "sulk" : ({ 0, ({
      "You sulk in the corner",
      "$mcname$ sulks in the corner" }) }),
  "swim" : ({ 0, ({
      "You give a good imitation of swimming", "$mcname$ swims around" }) }),
  "tackle" : ({ ({ 0, "%s", }), ({
      "You tackle $hcname$ in the $arg:chest,leg,arm,nose,knee,head,"+
      "foot,toe,finger$",
      "$mcname$ tackles you in the $lastarg$",
      "$mcname$ tackles $hcname$ in the $lastarg$", }) }),
  "tap" : ({ ({ 
      0, "%s", 2, "%s on the %s", 2, "%s on %s",
      2, "%s %s", 1, "%s %s", 3, "%s" }), ({ /* this is furrys */
      "You tap your $arg:foot,head,left leg,right leg,fingers,nose,"+
      "shoulder,teeth,arm$ impatiently",
      "$mcname$ taps $mposs$ $lastarg$ impatiently",
      "You tap $hcname$ on the $arg:shoulder,head,arm,nose,leg,teeth,foot,ear,"+
      "frog,other thing$",
      "$mcname$ taps you on the $lastarg$",
      "$mcname$ taps $hcname$ on the $lastarg$" }) }),
  "taunt" : ({ ({ 0, "%s" }), ({
      "You taunt yourself",
      "$mcname$ taunts $mposs$sely, how strange",
      "You taunt $hcname$",
      "$mcname$ taunts you",
      "$mcname$ taunts $hcname$" }) }),
  "tease" : ({ ({ 0, "%s", 1, "%s %s", 2, "%s %s", }), ({
      "You tease yourself",
      "$mcname$ teases $mbj$self, he appears to enjoy it",
      "You tease $hcname$ $arg:mercilessly,insistently,annoyingly,"+
      "lovingly,mischievously,rudely,carefully,quickly,slowly,"+
      "halfheartedly,idlely,obnoxiously$",
      "$mcname$ teases you $lastarg$",
      "$mcname$ teases $hcname$ $lastarg$", }) }),
  "thank" : ({ ({ 0, "%s", 2, "%s %s" }), ({
      "You thank $hcname$$ifarg: $arg:profusely,gratuitously,lots,slightly,"+
      "reservedly,solemnly,with all your hart$~$",
      "$mcname$ thanks you$ifarg: $lastarg$~$",
      "$mcname$ thanks $hcname$$ifarg: $lastarg$~$" }) }),
  "think" : ({ ({ 3, "%s", }), ({
      "You think $ifarg:$arg:#$$else$carefully~$",
      "$mcname$ thinks $ifarg:$lastarg$$else$carefully~$" }) }),
  "throw" : ({ ({ 0, "%s" }), ({
      "Hi yyyyaaa",
      "$mcname$ throws you to the floor$force#smile h at $mname$#2$",
      "$mcname$ throws $hcname$ to the floor in a happy embrace" }) }),
  "thwok" : ({ ({ 0, "%s"  }), ({
      "T H W O K K ! !",
      "$mcname$ \"T H W O K K ! !\"s",
      "You thwok $hcname$",
      "You are summarily thwokked by $mcname$",
      "$mcname$ thwoks $hcname$" }) }),
  "tickle" : ({ ({ 0,"%s", 1, "%s %s", 2, "%s %s" }), ({
      "You tickle $hcname$$ifarg: $arg:mercilessly,ruthlessly,fearlessly,"+
      "quickly,sneakily,weakly,carefully,gently,harshly,inconcievablely"+
      "slowly$~$",
      "$mcname$ tickles you$force#giggle#2$$ifarg: $lastarg$~$",
      "$mcname$ tickles $hcname$$ifarg: $lastarg$~$" }) }),
  "tongue" : ({ ({ 0,"%s", }), ({
      "You poke your tongue out at $hcname$",
      "$mcname$ pokes $mposs$ tongue out at you",
      "$mcname$ pokes $mposs$ tongue out at $hcname$", }) }),
  "tremble" : ({ ({ 3, "%s" }), ({
      "You tremble $arg:in fear,in nervousness,in pain,slightly,violently,"+
      "insistently,carefully,in a pink fit,in anticip.......pation$",
      "$mcname$ trembles $lastarg$", }), }),
  "trip" : ({ ({ 0, "%s" }), ({
      "You trip up",
      "$mcname$ trips up",
      "You trip $hcname$",
      "$mcname$ trips you",
      "$mcname$ trips $hcname$" }) }),
  "tweak" : ({ ({ 0, "%s", 1, "%s %s", 2, "%s %s", }), ({
      "You tweak $mhcname$ $arg:bottom,ear,arm,leg,nose,bits,beak$",
      "$mcname$ tweaks your $lastarg$",
      "$mcname$ tweaks $mhcname$ $lastarg$" }), }),
  "twiddle" : ({ ({ 3, "%s" }), ({
      "You twiddle your $arg:thumbs,fingers,hair,nose,feathers$",
      "$mcname$ twiddles $mposs$ $lastarg$" }) }),
  "twitch" : ({ 0, ({
      "You twitch your $arg:nose,arm,body,finger,igloo$",
      "$mcname$ twitches $mposs$ $lastarg$" }) }),
  "waggle" : ({ ({ 0, "%s", 0, "at %s" }), ({
      "$ifarg:You waggle your $arg:arm,leg,head,nose,ear,bottom,wings,"+
      "toe$$else$What did $hcname$ do wrong??!?~$",
      "$mcname$ waggles $mposs$ $ifarg:$lastarg$$else$finger~$ at you",
      "$mcname$ waggles $mposs$ $ifarg:$lastarg$$else$finger~$ at $hcname$",
    }) }),
  "wait" : ({ ({
      0, "%s", 0, "for %s", 0, "for %s %s", 1, "%s %s",
      0, "for %s", 1, "%s for %s",
      2, "%s %s", 3, "%s" }), ({
      "You wait$ifarg: $arg:patiently,impatiently,sleepily,lazily,sadly,"+
      "happily,tiredly,forlornly,excitedly,longingly$~$",
      "$mcname$ waves$ifarg: $lastarg$~$",
      "You wait$ifarg: $arg:patiently,impatiently,sleepily,lazily,sadly,"+
      "happily,tiredly,forlornly,excitedly,longingly$~$ for $hcname$",
      "$mcname$ waits$ifarg: $lastarg$~$ for you",
      "$mcname$ waits$ifarg: $lastarg$~$ for $hcname$" }) }),
  "waltz" : ({ ({ 0, "%s", }), ({
      "You waltz around the room with $hcname$",
      "$mcname$ waltzes around the room with you",
      "$mcname$ waltzes around the room with $hcname$", }) }),
  "wave" : ({ ({
      0, "%s", 0, "at %s", 0, "to %s", 2, "at %s %s", 1, "%s %s", 
      1, "%s to %s", 2, "to %s %s", 0, "at %s", 1, "%s at %s",
      2, "%s %s", 3, "%s" }), ({
      "You wave$ifarg: $arg:tiredly,sleepily,profunctialy,lazily,sadly,"+
      "happily,redundantly,forlornly,excitedly,longingly,pointlessly,"+
      "your wings,your feathers,your tentacles,your roots$~$",
      "$mcname$ waves$ifarg: $lastarg$~$",
      "You wave$ifarg: $arg:sleepily,tiredly,profunctialy,lazily,sadly,"+
      "happily,forlornly,excitedly,longingly,redundantly,pointlessly,"+
      "passionately,greenly,your wings,your feathers,"+
      "your tentacles$~$ to $hcname$",
      "$mcname$ waves$ifarg: $lastarg$~$ to you",
      "$mcname$ waves$ifarg: $lastarg$~$ to $hcname$" }) }),
  "welcome" : ({ ({ 0, "%s %s", 2, "%s to %s", 3, "%s" }), ({
      "You say WELCOME $arg:appreciatively,loudly,musically,pleasantly,"+
      "discordantly,happily,with a thick ironic tone$",
      "$mcname$ says WELCOME $lastarg$",
      "You welcome $hcname$ $arg:to the mud,loudly,musically,pleasantly,"+
      "discordantly,happily,appreciatively$",
      "$mcname$ welcomes you $lastarg$",
      "$mcname$ welcomes $hcname$ $lastarg$" }) }),
  "wibble" : ({ ({ 3, "%s" }), ({
      "You wibble $arg:loudly,constantly,annoyingly,"+
      "around,up,down,sideways$",
      "$mcname$ wibbles $lastarg$", }) }),
  "whimper" : ({ ({ 3, "%s" }), ({
      "You whimper$ifarg: $arg:painfully,fearfully,carefully,dimuatively,"+
      "happily,winningly,in triumph,with the wombles$~$",
      "$mcname$ whimpers$ifarg: $lastarg$~$", }), }),
  "wicker" : ({ 0, ({
      "You wicker like a horse",
      "$mcname$ wickers like a horse", }) }),
  "whistle" : ({ ({ 0, "%s %s", 2, "%s at %s", 3, "%s" }), ({
      "You whistle $arg:innocently,appreciatively,loudly,musically,pleasantly,"+
      "discordantly$",
      "$mcname$ whistles $lastarg$",
      "You whistle $arg:appreciatively,innocently,loudly,musically,pleasantly,"+
      "discordantly$",
      "$mcname$ whistles $lastarg$ at you",
      "$mcname$ whistles $lastarg$ at $hcname$" }) }),
  "wince" : ({ 0, ({ "You wince", "$mcname$ winces" }) }),
  "wiggle" : ({ ({ 0, "%s", 2, "%s at %s", 3, "%s" }), ({
      "You wiggle your bottom$ifarg: $arg:enticingly,suggestively,vigorously,"+
      "arrogantly,nonchalantly,quickly$~$",
      "$mcname$ wiggles $mposs$ bottom$ifarg: $lastarg$~$",
      "You wiggle your bottom$ifarg: $arg:enticingly,suggestively,vigorously,"+
      "arrogantly,nonchalantly,quickly$~$ at $hcname$",
      "$mcname$ wiggles $mposs$ bottom$ifarg: $lastarg$~$ at you",
      "$mcname$ wiggles $mposs$ bottom$ifarg: $lastarg$~$ at $hcname$" }) }),
  "wink" : ({ ({ 0, "%s", 0, "at %s", 1, "%s at %s", 1, "%s %s",
      2, "at %s %s", 2, "%s %s", 3, "%s" }), ({
      "You wink$ifarg: $arg:suggestively,broadly,slowly,loudly,grumpily,"+
      "despairingly,coyly,desperately,insolently,curtly,lovingly,"+
      "patiently,sadisticly,warily,seductive,lazily$~$",
      "$mcname$ winks$ifarg: $lastarg$~$",
      "You wink$ifarg: $arg:suggestively,broadly,slowly,loudly,grumpily,"+
      "despairingly,coyly,desperately,insolently,curtly,lovingly,"+
      "patiently,sadisticly,warily,seductive,lazily$~$ at $hcname$",
      "$mcname$ winks$ifarg: $lastarg$~$ at you",
      "$mcname$ winks$ifarg: $lastarg$~$ at $hcname$" }) }),
  "wipe" : ({ ({ 0, "%s", 0, "on %s", 1, "%s on %s" }), ({
      "You wipe the sweat from your brow",
      "$mcname$ wipes the sweat from $mposs$ brow",
      "You wipe your $arg:hands,leg,arm,nose$ on $hcname$",
      "$mcname$ wipes $mposs$ $lastarg$ on you",
      "$mcname$ wipes $mposs$ $lastarg$ on $hcname$" }) }),
  "wobble" : ({ ({ 3, "%s" }), ({
      "You wobble $arg:around a bit,like jelly,unsteadily,"+
      "happily$",
      "$mcname$ wobbles $lastarg$", }) }),
  "womble" : ({ ({ 3, "%s" }), ({ 
      "You womble around$ifarg: $arg:#$~$",
      "$mcname$ wombles around$ifarg: $lastarg$~$", }) }),
  "womple" : ({ ({ 0, "%s", 0, "at %s", 1, "%s at %s", 2, "at %s %s",
      1, "%s %s", 2, "%s %s", 3, "%s" }), ({
      "You womple$ifarg: $arg:manically,evilly,wickedly,insanely,mischievously,"+
      "impishly,cheekily,idiotically,tentatively,"+
      "like a duck with a flexible beak$~$",
      "$mcname$ womples$ifarg: $lastarg$~$",
      "You womple$ifarg: $arg:manically,evilly,wickedly,insanely,mischievously,"+
      "impishly,cheekily,idiotically,"+
      "like a duck with a flexible beak$~$ at $hcname$",
      "$mcname$ womples$ifarg: $lastarg$~$ at you",
      "$mcname$ womples$ifarg: $lastarg$~$ at $hcname$" }) }),
  "wonder" : ({ ({ 3, "%s" }), ({
      "You wonder $ifarg:$arg:#$$else$about reality and how "+
      "boring it can be~$",
      "$mcname$ wonder $ifarg:$arg:#$$else$about reality and how "+
      "boring it can be~$", }) }),
  "worship" : ({ ({ 0, "%s", 3, "%s" }), ({
      "You worship $ifarg:$arg:#$$else$Ducky~$",
      "$mcname$ worships $ifarg:$lastarg$$else$pinkfish~$",
      "You worship $hcname$",
      "$mcname$ worships you", "$mcname$ worships $hcname$" }) }),
  "yawn" : ({ ({ 3, "%s" }), ({
      "You yawn $arg:tiredly,boredly,sleepily$",
      "$mcname$ yawns $lastarg$" }) }) ,
  "zip" : ({ ({ 0, "%s" }), ({
      "You zip around the room",
      "$mcname$ zips around the room",
      "You zip around $hcname$",
      "$mcname$ zips around you",
      "$mcname$ zips around $hcname$", }), }),
]);

