./asm $1
cp "${1%.s}.cor" "mine.cor"
./resources/asm $1
cp "${1%.s}.cor" "ofi.cor"
hexdump -C mine.cor > mine
hexdump -C ofi.cor > ofi
ccdiff mine ofi
rm mine ofi ${1%.s}.cor mine.cor ofi.cor