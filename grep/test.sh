# SETTINGS:
# ---------
filename1=song.txt;
filename2=song2.txt;
filename3=lyrics3.txt; # filename3 is also used for -f flag as file for patterns
q="-q"; # delete -q for verbose mode
pattern=the;
show_commands=false;
# ---------

echo  *GREP 1 Just a pattern with two files
if [ "$show_commands" = true ]; then
echo  {grep "$pattern" "$filename2" "$filename1"}  {./s21_grep "$pattern" "$filename2" "$filename1"}
fi
diff <(grep "$pattern" "$filename2" "$filename1") <(./s21_grep "$pattern" "$filename2" "$filename1") -s $q
# -------------------------------------------------
echo  *GREP 1 -e with two files
if [ "$show_commands" = true ]; then
echo  {grep -e "$pattern" "$filename2" "$filename1"}  {./s21_grep -e "$pattern" "$filename2" "$filename1"}
fi
diff <(grep -e "$pattern" "$filename2" "$filename1") <(./s21_grep -e "$pattern" "$filename2" "$filename1") -s $q
# -------------------------------------------------
echo  *GREP 2 -i
if [ "$show_commands" = true ]; then
echo  {grep -i "$pattern" "$filename1"}  {./s21_grep -i "$pattern" "$filename1"}
fi
diff <(grep -i "$pattern" "$filename1") <(./s21_grep -i "$pattern" "$filename1") -s $q
# -------------------------------------------------
echo  *GREP 3 -v
if [ "$show_commands" = true ]; then
echo  {grep -v "$pattern" "$filename1"}  {./s21_grep -v "$pattern" "$filename1"}
fi
diff <(grep -v "$pattern" "$filename1") <(./s21_grep -v "$pattern" "$filename1") -s $q
# -------------------------------------------------
echo  *GREP 4 -c
if [ "$show_commands" = true ]; then
echo  {grep -c "$pattern" "$filename1"}  {./s21_grep -c "$pattern" "$filename1"}
fi
diff <(grep -c "$pattern" "$filename1") <(./s21_grep -c "$pattern" "$filename1") -s $q
# -------------------------------------------------
echo  *GREP 5 -l with three files
if [ "$show_commands" = true ]; then
echo  {grep -l "$pattern" "$filename2" "$filename3" "$filename1"}  {./s21_grep -l "$pattern" "$filename2" "$filename3" "$filename1"}
fi
diff <(grep -l "$pattern" "$filename2" "$filename3" "$filename1") <(./s21_grep -l "$pattern" "$filename2" "$filename3" "$filename1") -s $q
# -------------------------------------------------
echo  *GREP 6 -n
if [ "$show_commands" = true ]; then
echo  {grep -n "$pattern" "$filename1"}  {./s21_grep -n "$pattern" "$filename1"} 
fi
diff <(grep -n "$pattern" "$filename1") <(./s21_grep -n "$pattern" "$filename1") -s $q
# -------------------------------------------------
echo  *GREP 7 BONUS -h
if [ "$show_commands" = true ]; then
echo  {grep -h "$pattern" "$filename1"}  {./s21_grep -h "$pattern" "$filename1"}
fi
diff <(grep -h "$pattern" "$filename1") <(./s21_grep -h "$pattern" "$filename1") -s $q
# -------------------------------------------------
echo  *GREP 8 BONUS -o
if [ "$show_commands" = true ]; then
echo  {grep -o "$pattern" "$filename1"}  {./s21_grep -o "$pattern" "$filename1"}
fi
diff <(grep -o "$pattern" "$filename1") <(./s21_grep -o "$pattern" "$filename1") -s $q
# -------------------------------------------------
echo  *GREP 9 BONUS -h with two files
if [ "$show_commands" = true ]; then
echo  {grep -h "$pattern" "$filename2" "$filename1"}  {./s21_grep -h "$pattern" "$filename2" "$filename1"}
fi
diff <(grep -h "$pattern" "$filename2" "$filename1") <(./s21_grep -h "$pattern" "$filename2" "$filename1") -s $q
# -------------------------------------------------
echo  *GREP 10 BONUS -s
if [ "$show_commands" = true ]; then
echo  {grep "$pattern" -s aboba}  {./s21_grep "$pattern" -s aboba}
fi
diff <(grep "$pattern" -s aboba) <(./s21_grep "$pattern" -s aboba) -s $q
# -------------------------------------------------
echo  *GREP 11 BONUS -f
if [ "$show_commands" = true ]; then
echo  {grep -f "$filename3" "$filename2"}  {./s21_grep -f "$filename3" "$filename2"}
fi
diff <(grep -f "$filename3" "$filename2") <(./s21_grep -f "$filename3" "$filename2") -s $q
# -------------------------------------------------
echo  *GREP 12 BONUS -in
if [ "$show_commands" = true ]; then
echo  {grep -in "$pattern" "$filename1"}  {./s21_grep -in "$pattern" "$filename1"}
fi
diff <(grep -in "$pattern" "$filename1") <(./s21_grep -in "$pattern" "$filename1") -s $q
# -------------------------------------------------
echo  *GREP 13 BONUS -cv
if [ "$show_commands" = true ]; then
echo  {grep -cv "$pattern" "$filename1"}  {./s21_grep -cv "$pattern" "$filename1"}
fi
diff <(grep -cv "$pattern" "$filename1") <(./s21_grep -cv "$pattern" "$filename1") -s $q
# -------------------------------------------------
echo  *GREP 14 BONUS -iv
if [ "$show_commands" = true ]; then
echo  {grep -iv "$pattern" "$filename1"}  {./s21_grep -iv "$pattern" "$filename1"}
fi
diff <(grep -iv "$pattern" "$filename1") <(./s21_grep -iv "$pattern" "$filename1") -s $q
# -------------------------------------------------
echo  *GREP 15 BONUS -lv with three files
if [ "$show_commands" = true ]; then
echo  {grep -lv "$pattern" "$filename2" "$filename3" "$filename1"}  {./s21_grep -lv "$pattern" "$filename2" "$filename3" "$filename1"}
fi
diff <(grep -lv "$pattern" "$filename2" "$filename3" "$filename1") <(./s21_grep -lv "$pattern" "$filename2" "$filename3" "$filename1") -s $q
# -------------------------------------------------
echo  *GREP 16 BONUS -ho with two files
if [ "$show_commands" = true ]; then
echo  {grep -ho "$pattern" "$filename2" "$filename1"}  {./s21_grep -ho "$pattern" "$filename2" "$filename1"}
fi
diff <(grep -ho "$pattern" "$filename2" "$filename1") <(./s21_grep -ho "$pattern" "$filename2" "$filename1") -s $q
# -------------------------------------------------
echo  *GREP 17 BONUS -nf
if [ "$show_commands" = true ]; then
echo  {grep -nf "$filename3" "$filename2"}  {./s21_grep -nf "$filename3" "$filename2"}
fi
diff <(grep -nf "$filename3" "$filename2") <(./s21_grep -nf "$filename3" "$filename2") -s $q
# -------------------------------------------------
echo  *Tests are over*
