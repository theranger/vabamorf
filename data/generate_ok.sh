#!/usr/bin/env bash

# Korjame jooksvasse kataloogi sõnastiku tegemiseks vajalikud
# failid kokku,
# grupeerime sisu järgi veidi ümber,
# eemaldame rea algusest allika-liigituse,
# teisendame nad utf-8 kujult 2-baidise unicode-i kujule
# ja teisendame nad selliseks, et iga sõna iga tüve juures on kirjas talle liituda võivate lõppude grupp

# Sisse (utf-8):
# loend1 ... loend10
# fs_lex
# fs_suf
# pref.pok

# Välja (ucs-2le):
#     mmm.ok       muutumatud sõnad
#     nomm.ok      käändsõnad ja mõned (?) muutumatud sõnad
#     verb.ok      tegusõnad
#     lgr          lõpugrupid
#     suf.sok      sufiksid
#     *.err        vigased sisendread

function generate_ok {
	echo "== loendid sortida ja UCkujule:"
	for f in 1 2 3 4 5 6 7 8 10
	do
	  cat ${MRF_DIR}/loend${f} \
	  | LC_COLLATE=C sort | LC_COLLATE=C uniq \
	  | iconv -f utf8 -t ucs-2le \
	  > loend${f} || exit 1
	done

	echo -n "== Prefiksid UCkujule: pref.pok --> "
	cat ${MRF_DIR}/pref.pok \
	  | iconv -f utf8 -t ucs-2le \
	  > pref.pok || exit 1
	echo "pref.pok"

	echo "== Genereerime failist fs_lex muutumatud:"
	for X in vvsm tesm sagem lisam
	do
	  cat ${MRF_DIR}/fs_lex \
		| grep "^${X}:" \
		| sed 's/\(^[a-z][^:]*:\)\(.*$\)/\2/g' \
		| iconv -f utf8 -t ucs-2le \
		>> mmm.pala.txt
	done
	echo "  --> mmm.pala.txt"

	echo "== Genereerime failist fs_lex käänduvad:"
	for X in vvs tes sage lisa lisatule xp voor voorxp
	do
	  cat ${MRF_DIR}/fs_lex \
		| grep "^${X}:" \
		| sed 's/\(^[a-z][^:]*:\)\(.*$\)/\2/g' \
		| iconv -f utf8 -t ucs-2le \
		>> nomm.pala.txt || exit 1
	done
	echo "  --> nomm.pala.txt"

	echo "== Genereerime failist fs_lex pöörduvad:"
	for X in vvsv tesv lisav xpv sagev
	do
	  cat ${MRF_DIR}/fs_lex \
		| grep "^${X}:" \
		| sed 's/\(^[a-z][^:]*:\)\(.*$\)/\2/g' \
		| iconv -f utf8 -t ucs-2le \
		>> verb.pala.txt || exit 1
	done
	echo "  --> verb.pala.txt"

	echo -n "fs_suf ->"
	cat ${MRF_DIR}/fs_suf \
	  | iconv -f utf8 -t ucs-2le \
	  > suf || exit 1
	echo " --> suf"

	# NB! sisend ja väljund on 2-baidine little-endian Unicode (mitte utf-8) !
	# Sisse:
	#   algne sõnastik
	# Esimene töödeldav fail võiks olla muutumatute sõnade fail, sest
	# siis saab esimeseks lõpugrupiks selline, mis esindab lõppude puudumist
	# (ja see võib olla edasises sõnastikupakkimises oluline)
	# Valja:
	#   ühel real on ühe sõna tüved koos lõpugruppidega
	# NB! lgr          sinna sudib lõpugruppe juurde
	#     mmm.ok       muutumatud sõnad
	#     nomm.ok      käändsõnad ja mõned (?) muutumatud sõnad
	#     verb.ok      tegusõnad
	#     lgr          lõpugrupid
	#     suf.sok      sufiksid
	#     *.err        vigased sisendread
	echo "== NIM/VRB-ime failid: X lgr --> X.[s]ok lgr"
	${BIN_DIR}/vabamorf-noom mmm.pala.txt  mmm.ok   mmm.err || exit 1
	${BIN_DIR}/vabamorf-noom nomm.pala.txt nomm.ok  nomm.err || exit 1
	${BIN_DIR}/vabamorf-verb verb.pala.txt verb.ok  verb.err || exit 1
	${BIN_DIR}/vabamorf-noom suf           suf.sok  suf.err  || exit 1

}
