	.cpu cortex-m0
	.data
string:
	.ascii "Wilhelmus van Nassouwe \n Ben ick@6%Duytsch@1#Bloedt,@?#D@?#Vaderland ghetr@Y(lijf@[%tot ind@i#doet;@U#E@c#Prince van Orangi@i#@U#@o#@S$vry onverveert.@o#D@_#Con@T#@=#@T#Hisp@V)Heb@V%altijt ghe@V%\n\nIn Godes vre@%#te lev@R4betracht,@m#Daerom@2#n@A%verdr@U'Om Land, @?#Luyd gheb@X%:@X#M@X# Godt sal my reger@X%Als e@b#goet Instrument,@U#Dat ick@S%wederke@T'In mijn@`#Regi@O$.\n\nLijdt U,@:% On@P#saten@j%ie oprecht z@>$van aert@<$Go@W#sal u niet verl@X$@W#Al@N$t ghy nu besw@U$:@U#Die vroom@5#ghe@k# te leven,@Y#Bidt Go@$#nacht ende d@*#.@[$at Hy my cr@=%wil @d#@[#@='ick u help@2#m@V$\n\nLijf@g&goed al te sam@T%Heb@T'niet verschoont,@<#Mijn Br@U#@6#, @7#ch van N@]$@A$@^#bent@^#@;#k@^$t@\$:@\#Graef Adolff is gheblev@W&In Vrieslandt in den Slach@=$Sijn siel@9#t eewich @[%@Z#Verw@G#t@R%jonghst@\#d@[#.\n\nEd@U#@k#Hoo@S#ghebor@V&an Keyserlick@i#stam:@o#E@f#Vorst des Rijcks verc@X$,@Y#Als e@c#vroom Christen-ma@=%Voor Go@[$W@*#t gheprees@\&Heb ick@\#ij onversaecht@Z$Als een helt zonder@G#@Z%@Y#Mijn edel bloet gew@Y%.\n\n@:%schi@W#e@V# betrouw@W%Zij@L#hy, O Godt, m@i$Heer.@>#Op U soo wil ick b@X%,@Y#Verlaet my nimmerm@S#;@S#Dat@J%doch vroom mag blijven@Y#U dienaer t'all@'#stond@Z$ie tyranny verdr@R%,@9'my mijn hert doorw@U#t.\n\nVal @\"#d@C&beswar@V&End@S&@m#volg@Z#s z@d#@<$M@l$Godt wilt doch@\#@[%@Z#D@%#trouw@-#dienaer@'#jn:@;$at sy my niet verassch@W%In h@K#@c#boos@j#moet,@T#H@a$hand@F#@V%@N#w@W-mijn on@i#uldich bl@[#.\n\nAls David@l$ste vlucht@W%Voor Saul d@g#tyran:@n#Soo heb ick@T$@K$s@S)Met menich edelm@R&Maer Godt@X#ef@%$m verheven,@U#Verlost uit ald@L#noot@9$Een Coninckrijck ghe@\"#@W#@V#In Israel, se@T#gr@U#.\n\nNa tsu@e#sal i@T#ontfan@Z#@U$Van Godt, mijn H@Y#, dat soe@4#\n Da@k#na@/# d@2# verl@])M@S$vorstelick @6#m@W)t is@k&@:$mag @F#rv@X&@i#eeren, in@C%vel@W%E@?#eeuwich rijk@8#rw@V(Als@V#n ghetrouwe h@V#.\n\nNiets doet my meer erbarm@V%In mijn@b#wedersp@G#,@n#Dan da@R#@E#s@a# ver@S(Des Conincks land@i#g@W)t ud de Spaengiaerts cre@M#en@B$O edel Neer@\$t s@['Als ick d@S#@[# gh@H#@V$@U$Mijn@X&hert@C#t bl@X#.\n\n@W$e@O#Prins op@W#set@`#@U#et m@Y#es@V#yr@&#cracht,@;#Van d@V#tyr@)#verm@T'Heb ick@<%sl@N#@<$w@V(Die, by Maestri@l# begraven@>$Bevreesde mijn ghewelt;@X#M@/$ruyters s@n# men d@Y%@X#Seer moedi@9#door dat v@\#.\n\nSoo het d@Q#wil@'#s H@P#@Y%Op die tijt had gheweest,@;#H@/#ick g@L#@Z%l@a#k@Y(Van u@\#t swaer temp@Y$:@Y#M@0$de H@Y# v@H#hi@A#bov@Y%Die a@l#@\#nck reg@F#t,@9'm@C#altijt moet l@U$@<$E@f#eeft@3#ni@8#b@W&.\n\nS@_# christlick was ghedre@Z#@Y#Mijn prince@?%@;#moet,@:#Stantvastich i@V%bl@V,hert in te@U#nsp@W'D@A#Heer@?#b ick@X%ed@W%Van m@[#es@]%@k#gron@V&at Hy@=% sae@W#wil r@X$@>$M@7$onschult do@n#oirc@\#.\n\nOorlof@[&arme @F#ap@X&Die zijt in groot@Y#n@&#.@;#U Herder sal niet sl@W(Al@V&ghy nu verstroit:@W#Tot Godt wilt u beghev@W&Sijn heylsaem woort neemt a@@&Als vrome Christen l@\(Tsal hier haest z@l$ghed@[#.\n\nV@m# Godt wil ick belijd@b#\n End s@O#@\#groot@d#macht,@;#Dat@N%tot@n$en@Q#t@X(D@^#Conin@o#heb ver@W$:@W%n d@['Godt @Q$Heere,@X%r hoochst@)#Maje@(#yt@:$H@g#moet@N#obedi@Q#n@R$I@o#@U#gh@b#chtich@P#.\n"
	.text
	.align 1
	.global print_asciz
	.global application
	.global invert
	
application:
	push {r0, lr }
	ldr r0, =string
	bl print_asciz
	pop { r0, pc }

print_asciz:
	push { r5, lr }
	mov r5, r0
loop:
	ldrb r0, [r5]
	add r0, r0, #0
	beq done
	bl invert
	bl put_char
	add r5, r5, #1
	b loop
done:
	pop { r5, pc }
	
invert:
	push { r1 - r5, lr}
	ldr r1, =( 'a' - 'A' )
	ldr r2, ='a'
	ldr r3, ='z'
	ldr r4, ='A'
	ldr r5, ='Z'
	cmp r0, r2
	bge greater_a
	cmp r0, r4
	bge greater_A
	b done_inv
greater_a:
	cmp r0, r3
	ble inversion_noncaps
	b done_inv
greater_A:
	cmp r0, r5
	ble inversion_caps
	b done_inv
inversion_noncaps:
	sub r0, r0, r1
	b done_inv
inversion_caps:
	add r0, r0, r1
done_inv:
	pop {r1 - r5, pc}