#!/usr/bin/env bash

function generate_disamb {
	# Sisendfail dct/data/yhh/all.cooked on sellisel kujul:
	# - Iga lause on omaette real.
	# - Punktuatsioon, sulud jms on sõnast lahku tõstetud.
	# - Igale sõnale, kirjavahemärgile jms järgneb tühikuga eraldatult ühestamismärgend.
	#
	# Ühestaja andmefail tehakse 2 programmi abil:
	# - dct-t3mesta -cio kodeering treeningkorpus
	# - dct-t3pakitud
	#
	# dct-t3mesta teeb tmp alamkataloogi treeningkorpuse põhjal failid:
	# - taglist.txt Ühestamismärgendite loend. Treeningkorpuses mittesinev ***VAHE*** on
	#   vajalik trigrammide tabelis lause alguse/lõpuga seotud märgendijärjendite tõenäosuste arvutamiseks.
	#   Fail on kujul: märgendi-indeks märgend
	# - margcnt.txt Ühestamismärgendi esinemiste arv. Fail on kujul: märgend esinemisarv
	# - 3grammid.txt Trigrammid. Fail on kujul: märgend märgend märgend tõenäosuse-logaritm
	# - klassid.txt Sõnest sõltumatult mitmesusklassid.
	#   Fail on kujul: märgendite-arv-klassis märgend[1]=tõenäosuse-logaritm[1] ... märgend[märgendite-arv-klassis]=tõenäosuse-logaritm[märgendite-arv-klassis]
	# - lex.txt Sõnest sõltuvad mitmesusklassid.
	#   Fail on kujul: sõne [märgendite-arv-klassis] märgend[1]=tõenäosuse-logaritm[1] ... märgend[märgendite-arv-klassis]=tõenäosuse-logaritm[märgendite-arv-klassis]
	#
	# dct-t3pakitud võtab jooksvast kataloogist dct-t3mesta tehtud 5 väljundfaili ja
	# teeb neist ühestamismooduli poolt kasutatava leksikonifaili et3.dct.


	echo "== " Teeme ühestaja andmefailid

	${BIN_DIR}/vabamorf-t3mesta ${YHH_DIR}/all.cooked
	${BIN_DIR}/vabamorf-t3pakitud

	cp et3.dct ${BIN_DIR}/et3.dct
	echo "== Ühestaja sõnastik failis:" ${BIN_DIR}/et3.dct
}
