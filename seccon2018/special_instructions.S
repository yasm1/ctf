
special_instructions:     file format elf32-bigmoxie


Disassembly of section .text:

00001400 <_start>:
    1400:	01 10 00 00 	ldi.l	$sp, 0x1c60
    1404:	1c 60 
    1406:	03 00 00 00 	jsra	15a2 <main>
    140a:	15 a2 

0000140c <__exit>:
    140c:	02 42       	mov	$r2, $r0
    140e:	30 00 00 00 	swi	0x1
    1412:	00 01 
    1414:	02 24       	mov	$r0, $r2
    1416:	04 00       	ret

00001418 <__read>:
    1418:	02 64       	mov	$r4, $r2
    141a:	02 53       	mov	$r3, $r1
    141c:	02 42       	mov	$r2, $r0
    141e:	30 00 00 00 	swi	0x4
    1422:	00 04 
    1424:	02 24       	mov	$r0, $r2
    1426:	04 00       	ret

00001428 <__write>:
    1428:	02 64       	mov	$r4, $r2
    142a:	02 53       	mov	$r3, $r1
    142c:	02 42       	mov	$r2, $r0
    142e:	30 00 00 00 	swi	0x5
    1432:	00 05 
    1434:	02 24       	mov	$r0, $r2
    1436:	04 00       	ret

00001438 <__open>:
    1438:	02 64       	mov	$r4, $r2
    143a:	02 53       	mov	$r3, $r1
    143c:	02 42       	mov	$r2, $r0
    143e:	30 00 00 00 	swi	0x2
    1442:	00 02 
    1444:	02 24       	mov	$r0, $r2
    1446:	04 00       	ret

00001448 <__close>:
    1448:	04 00       	ret

0000144a <exit>:
    144a:	91 18       	dec	$sp, 0x18
    144c:	03 00 00 00 	jsra	140c <__exit>
    1450:	14 0c 

00001452 <write1>:
    1452:	91 18       	dec	$sp, 0x18
    1454:	37 03 00 10 	sto.b	0x10($fp), $r1
    1458:	02 30       	mov	$r1, $fp
    145a:	83 10       	inc	$r1, 0x10
    145c:	01 40 00 00 	ldi.l	$r2, 0x1
    1460:	00 01 
    1462:	03 00 00 00 	jsra	1428 <__write>
    1466:	14 28 
    1468:	04 00       	ret

0000146a <putchar>:
    146a:	06 18       	push	$sp, $r6
    146c:	91 18       	dec	$sp, 0x18
    146e:	02 83       	mov	$r6, $r1
    1470:	03 00 00 00 	jsra	1452 <write1>
    1474:	14 52 
    1476:	02 28       	mov	$r0, $r6
    1478:	02 e0       	mov	$r12, $fp
    147a:	9e 04       	dec	$r12, 0x4
    147c:	07 e8       	pop	$r12, $r6
    147e:	04 00       	ret

00001480 <puts>:
    1480:	06 18       	push	$sp, $r6
    1482:	06 19       	push	$sp, $r7
    1484:	06 1a       	push	$sp, $r8
    1486:	06 1b       	push	$sp, $r9
    1488:	06 1c       	push	$sp, $r10
    148a:	91 18       	dec	$sp, 0x18
    148c:	02 92       	mov	$r7, $r0
    148e:	02 83       	mov	$r6, $r1
    1490:	1c 33       	ld.b	$r1, ($r1)
    1492:	02 43       	mov	$r2, $r1
    1494:	2e 22       	xor	$r0, $r0
    1496:	0e 42       	cmp	$r2, $r0
    1498:	c0 0b       	beq	14b0 <puts+0x30>
    149a:	01 c0 00 00 	ldi.l	$r10, 0x146a
    149e:	14 6a 
    14a0:	02 a2       	mov	$r8, $r0
    14a2:	02 29       	mov	$r0, $r7
    14a4:	19 c0       	jsr	$r10
    14a6:	88 01       	inc	$r6, 0x1
    14a8:	1c 38       	ld.b	$r1, ($r6)
    14aa:	02 23       	mov	$r0, $r1
    14ac:	0e 2a       	cmp	$r0, $r8
    14ae:	c7 f9       	bne	14a2 <puts+0x22>
    14b0:	2e 22       	xor	$r0, $r0
    14b2:	02 e0       	mov	$r12, $fp
    14b4:	9e 14       	dec	$r12, 0x14
    14b6:	07 ec       	pop	$r12, $r10
    14b8:	07 eb       	pop	$r12, $r9
    14ba:	07 ea       	pop	$r12, $r8
    14bc:	07 e9       	pop	$r12, $r7
    14be:	07 e8       	pop	$r12, $r6
    14c0:	04 00       	ret

000014c2 <putxval>:
    14c2:	06 18       	push	$sp, $r6
    14c4:	06 19       	push	$sp, $r7
    14c6:	06 1a       	push	$sp, $r8
    14c8:	06 1b       	push	$sp, $r9
    14ca:	06 1c       	push	$sp, $r10
    14cc:	91 2c       	dec	$sp, 0x2c
    14ce:	2e 55       	xor	$r3, $r3
    14d0:	37 05 ff eb 	sto.b	0xffeb($fp), $r3
    14d4:	2e 55       	xor	$r3, $r3
    14d6:	0e 35       	cmp	$r1, $r3
    14d8:	c4 05       	bne	14e4 <putxval+0x22>
    14da:	0e 45       	cmp	$r2, $r3
    14dc:	c4 03       	bne	14e4 <putxval+0x22>
    14de:	01 40 00 00 	ldi.l	$r2, 0x1
    14e2:	00 01 
    14e4:	02 50       	mov	$r3, $fp
    14e6:	95 16       	dec	$r3, 0x16
    14e8:	2e 66       	xor	$r4, $r4
    14ea:	1b c0 00 00 	ldi.b	$r10, 0x30
    14ee:	00 30 
    14f0:	01 a0 00 00 	ldi.l	$r8, 0x1640
    14f4:	16 40 
    14f6:	01 90 00 00 	ldi.l	$r7, 0xf
    14fa:	00 0f 
    14fc:	01 80 00 00 	ldi.l	$r6, 0x4
    1500:	00 04 
    1502:	1a 00 00 00 	jmpa	151e <putxval+0x5c>
    1506:	15 1e 
    1508:	02 73       	mov	$r5, $r1
    150a:	26 79       	and	$r5, $r7
    150c:	02 ba       	mov	$r9, $r8
    150e:	05 b7       	add	$r9, $r5
    1510:	1c 7b       	ld.b	$r5, ($r9)
    1512:	1e 57       	st.b	($r3), $r5
    1514:	27 38       	lshr	$r1, $r6
    1516:	0e 46       	cmp	$r2, $r4
    1518:	c0 01       	beq	151c <putxval+0x5a>
    151a:	94 01       	dec	$r2, 0x1
    151c:	95 01       	dec	$r3, 0x1
    151e:	0e 36       	cmp	$r1, $r4
    1520:	c7 f3       	bne	1508 <putxval+0x46>
    1522:	0e 46       	cmp	$r2, $r4
    1524:	c0 04       	beq	152e <putxval+0x6c>
    1526:	1e 5c       	st.b	($r3), $r10
    1528:	1a 00 00 00 	jmpa	151a <putxval+0x58>
    152c:	15 1a 
    152e:	02 35       	mov	$r1, $r3
    1530:	83 01       	inc	$r1, 0x1
    1532:	03 00 00 00 	jsra	1480 <puts>
    1536:	14 80 
    1538:	2e 22       	xor	$r0, $r0
    153a:	02 e0       	mov	$r12, $fp
    153c:	9e 14       	dec	$r12, 0x14
    153e:	07 ec       	pop	$r12, $r10
    1540:	07 eb       	pop	$r12, $r9
    1542:	07 ea       	pop	$r12, $r8
    1544:	07 e9       	pop	$r12, $r7
    1546:	07 e8       	pop	$r12, $r6
    1548:	04 00       	ret

0000154a <set_random_seed>:
    154a:	16 20       	bad
    154c:	04 00       	ret

0000154e <get_random_value>:
    154e:	17 20       	bad
    1550:	04 00       	ret

00001552 <decode>:
    1552:	06 18       	push	$sp, $r6
    1554:	06 19       	push	$sp, $r7
    1556:	06 1a       	push	$sp, $r8
    1558:	06 1b       	push	$sp, $r9
    155a:	06 1c       	push	$sp, $r10
    155c:	06 1d       	push	$sp, $r11
    155e:	91 18       	dec	$sp, 0x18
    1560:	02 d2       	mov	$r11, $r0 # arg0 (enc_flag)
    1562:	1c 42       	ld.b	$r2, ($r0)
    1564:	2e 22       	xor	$r0, $r0
    1566:	0e 42       	cmp	$r2, $r0
    1568:	c0 12       	beq	158e <decode+0x3c>
    156a:	02 a3       	mov	$r8, $r1 # arg1 (randval)
    156c:	02 9d       	mov	$r7, $r11 # arg0 (flag)
    156e:	01 c0 00 00 	ldi.l	$r10, 0x154e # get_random_value
    1572:	15 4e 
    1574:	1c 8a       	ld.b	$r6, ($r8) # $r6 = *randval JUMP HERE
    1576:	2e 22       	xor	$r0, $r0
    1578:	19 c0       	jsr	$r10 # $r0 = get_random_value()
    157a:	2e 82       	xor	$r6, $r0 # $t6 = *randval ^ get_random_value()
    157c:	1c 29       	ld.b	$r0, ($r7) # $r0 = *flag
    157e:	2e 82       	xor	$r6, $r0 # $r0 = *randval & get_random_value() ^ flag
    1580:	1e 98       	st.b	($r7), $r6 # *flag = $r0
    1582:	89 01       	inc	$r7, 0x1 # flag++
    1584:	8a 01       	inc	$r8, 0x1 # randval++
    1586:	1c 39       	ld.b	$r1, ($r7)
    1588:	2e 22       	xor	$r0, $r0
    158a:	0e 32       	cmp	$r1, $r0
    158c:	c7 f3       	bne	1574 <decode+0x22> # if(!*flag) break;
    158e:	02 2d       	mov	$r0, $r11
    1590:	02 e0       	mov	$r12, $fp
    1592:	9e 18       	dec	$r12, 0x18
    1594:	07 ed       	pop	$r12, $r11
    1596:	07 ec       	pop	$r12, $r10
    1598:	07 eb       	pop	$r12, $r9
    159a:	07 ea       	pop	$r12, $r8
    159c:	07 e9       	pop	$r12, $r7
    159e:	07 e8       	pop	$r12, $r6
    15a0:	04 00       	ret

000015a2 <main>:
    15a2:	06 18       	push	$sp, $r6
    15a4:	91 18       	dec	$sp, 0x18
    15a6:	01 20 92 d6 	ldi.l	$r0, 0x92d68ca2
    15aa:	8c a2 
    15ac:	03 00 00 00 	jsra	154a <set_random_seed>
    15b0:	15 4a 
    15b2:	01 80 00 00 	ldi.l	$r6, 0x1480
    15b6:	14 80 
    15b8:	01 20 00 00 	ldi.l	$r0, 0x1
    15bc:	00 01 
    15be:	01 30 00 00 	ldi.l	$r1, 0x1654
    15c2:	16 54 
    15c4:	19 80       	jsr	$r6
    15c6:	01 20 00 00 	ldi.l	$r0, 0x1
    15ca:	00 01 
    15cc:	01 30 00 00 	ldi.l	$r1, 0x1680
    15d0:	16 80 
    15d2:	19 80       	jsr	$r6
    15d4:	01 20 00 00 	ldi.l	$r0, 0x1
    15d8:	00 01 
    15da:	01 30 00 00 	ldi.l	$r1, 0x169c
    15de:	16 9c 
    15e0:	19 80       	jsr	$r6
    15e2:	01 20 00 00 	ldi.l	$r0, 0x1
    15e6:	00 01 
    15e8:	01 30 00 00 	ldi.l	$r1, 0x16ac
    15ec:	16 ac 
    15ee:	19 80       	jsr	$r6
    15f0:	01 20 00 00 	ldi.l	$r0, 0x1
    15f4:	00 01 
    15f6:	01 30 00 00 	ldi.l	$r1, 0x16c4
    15fa:	16 c4 
    15fc:	19 80       	jsr	$r6
    15fe:	01 20 00 00 	ldi.l	$r0, 0x1
    1602:	00 01 
    1604:	01 30 00 00 	ldi.l	$r1, 0x16e0
    1608:	16 e0 
    160a:	19 80       	jsr	$r6
    160c:	01 20 00 00 	ldi.l	$r0, 0x1800
    1610:	18 00 
    1612:	01 30 00 00 	ldi.l	$r1, 0x1820
    1616:	18 20 
    1618:	03 00 00 00 	jsra	1552 <decode>
    161c:	15 52 
    161e:	02 32       	mov	$r1, $r0
    1620:	01 20 00 00 	ldi.l	$r0, 0x1
    1624:	00 01 
    1626:	19 80       	jsr	$r6
    1628:	01 20 00 00 	ldi.l	$r0, 0x1
    162c:	00 01 
    162e:	01 30 00 00 	ldi.l	$r1, 0x167c
    1632:	16 7c 
    1634:	19 80       	jsr	$r6
    1636:	2e 22       	xor	$r0, $r0
    1638:	03 00 00 00 	jsra	144a <exit>
    163c:	14 4a 

Disassembly of section .rodata:

00001640 <_erodata-0xb0>:
    1640:	30 31 32 33 	swi	0x32333435
    1644:	34 35 
    1646:	36 37 38 39 	ldo.b	$r1, 0x3839($r5)
    164a:	61 62       	bad
    164c:	63 64       	bad
    164e:	65 66       	bad
    1650:	00 00       	bad
    1652:	00 00       	bad
    1654:	54 68       	bad
    1656:	69 73       	bad
    1658:	20 70 72 6f 	ldi.s	$r5, 0x726f6772
    165c:	67 72 
    165e:	61 6d       	bad
    1660:	20 75 73 65 	ldi.s	$r5, 0x73657320
    1664:	73 20 
    1666:	73 70       	bad
    1668:	65 63       	bad
    166a:	69 61       	bad
    166c:	6c 20       	bad
    166e:	69 6e       	bad
    1670:	73 74       	bad
    1672:	72 75       	bad
    1674:	63 74       	bad
    1676:	69 6f       	bad
    1678:	6e 73       	bad
    167a:	2e 0a       	xor	$fp, $r8
    167c:	0a 00       	ld.l	$fp, ($fp)
    167e:	00 00       	bad
    1680:	53 45       	bad
    1682:	54 52       	bad
    1684:	53 45       	bad
    1686:	45 44       	bad
    1688:	3a 20       	bad
    168a:	28 4f       	ashl	$r2, $r13
    168c:	70 63       	bad
    168e:	6f 64       	bad
    1690:	65 3a       	bad
    1692:	30 78 31 36 	swi	0x3136290a
    1696:	29 0a 
    1698:	00 00       	bad
    169a:	00 00       	bad
    169c:	09 52 65 67 	sta.l	0x65674120, $r3
    16a0:	41 20 
    16a2:	2d 3e       	ashr	$r1, $r12
    16a4:	20 53 45 45 	ldi.s	$r3, 0x4545440a
    16a8:	44 0a 
    16aa:	0a 00       	ld.l	$fp, ($fp)
    16ac:	47 45       	bad
    16ae:	54 52       	bad
    16b0:	41 4e       	bad
    16b2:	44 3a       	bad
    16b4:	20 28 4f 70 	ldi.s	$r0, 0x4f70636f
    16b8:	63 6f 
    16ba:	64 65       	bad
    16bc:	3a 30       	bad
    16be:	78 31       	bad
    16c0:	37 29 0a 00 	sto.b	0xa00($r0), $r7
    16c4:	09 78 6f 72 	sta.l	0x6f727368, $r5
    16c8:	73 68 
    16ca:	69 66       	bad
    16cc:	74 33       	bad
    16ce:	32 28       	udiv	$r0, $r6
    16d0:	53 45       	bad
    16d2:	45 44       	bad
    16d4:	29 20       	sub	$r0, $fp
    16d6:	2d 3e       	ashr	$r1, $r12
    16d8:	20 53 45 45 	ldi.s	$r3, 0x4545440a
    16dc:	44 0a 
    16de:	00 00       	bad
    16e0:	09 53 45 45 	sta.l	0x45454420, $r3
    16e4:	44 20 
    16e6:	2d 3e       	ashr	$r1, $r12
    16e8:	20 52 65 67 	ldi.s	$r3, 0x6567410a
    16ec:	41 0a 
    16ee:	0a 00       	ld.l	$fp, ($fp)

Disassembly of section .data:

00001800 <flag>:
    1800:	6d 72       	bad
    1802:	c3 e2       	beq	17c8 <_erodata+0xd8>
    1804:	cf 95       	bgt	1730 <_erodata+0x40>
    1806:	54 9d       	bad
    1808:	b6 ac       	ssr	$r4, 0xac
    180a:	03 84 c3 c2 	jsra	c3c23593 <_end+0xc3c21933>
    180e:	35 93 
    1810:	c3 d7       	beq	17c0 <_erodata+0xd0>
    1812:	7c e2       	bad
    1814:	dd d4       	ble	1bbe <_ebss+0x35e>
    1816:	ac 5e       	gsr	$r10, 0x5e
    1818:	99 c9       	dec	$r7, 0xc9
    181a:	a5 34       	gsr	$r3, 0x34
    181c:	de 06       	ble	142a <__write+0x2>
    181e:	4e 00       	bad

00001820 <randval>:
    1820:	3d 05       	bad
    1822:	dc 31       	ble	1886 <_ebss+0x26>
    1824:	d1 8a       	bltu	1b3a <_ebss+0x2da>
    1826:	af 29       	gsr	$r13, 0x29
    1828:	96 fa       	dec	$r4, 0xfa
    182a:	cb 1b       	blt	1662 <_etext+0x24>
    182c:	01 ec e2 f7 	ldi.l	$r12, 0xe2f71570
    1830:	15 70 
    1832:	6c f4       	bad
    1834:	7e a1       	bad
    1836:	9e 0e       	dec	$r12, 0xe
    1838:	01 f9 c2 4c 	ldi.l	$r13, 0xc24cbaa0
    183c:	ba a0 
    183e:	a1 08       	gsr	$sp, 0x8
    1840:	70 24       	bad
    1842:	85 8a       	inc	$r3, 0x8a
    1844:	4d 2d       	bad
    1846:	3c 02       	bad
    1848:	fc 6f       	bad
    184a:	20 f0 c7 ad 	ldi.s	$r13, 0xc7ad2f97
    184e:	2f 97 
    1850:	2b cc       	or	$r10, $r10
    1852:	a3 34       	gsr	$r1, 0x34
    1854:	23 53       	st.s	($r3), $r1
    1856:	c9 b7       	blt	1bc6 <_ebss+0x366>
    1858:	0c 10 6c 0e 	ldo.l	$sp, 0x6c0e($fp)
    185c:	fa f9       	bad
    185e:	a1 9a       	gsr	$sp, 0x9a

Disassembly of section .stack:

00001860 <_end-0x400>:
	...

Disassembly of section .comment:

00000000 <.comment>:
   0:	47 43       	bad
   2:	43 3a       	bad
   4:	20 28 47 4e 	ldi.s	$r0, 0x474e5529
   8:	55 29 
   a:	20 34 2e 39 	ldi.s	$r1, 0x2e392e34
   e:	2e 34 
	...
