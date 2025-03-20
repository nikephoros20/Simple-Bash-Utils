filename=ASCII;
echo Testing -A flag
diff <(cat -A "$filename") <(./s21_cat -A "$filename") -s
echo Testing -b flag
diff <(cat -b "$filename") <(./s21_cat -b "$filename") -s
echo Testing -e flag
diff <(cat -e "$filename") <(./s21_cat -e "$filename") -s
echo Testing -n flag
diff <(cat -n "$filename") <(./s21_cat -n "$filename") -s
# echo ----------------------------------------------*CAT 4
# diff <(cat "$filename" -n) <(./s21_cat "$filename" -n) -s
echo Testing -s flag
diff <(cat -s "$filename") <(./s21_cat -s "$filename") -s
echo Testing -t flag
diff <(cat -t "$filename") <(./s21_cat -t "$filename") -s
echo Testing with no flag
diff <(cat "$filename") <(./s21_cat "$filename") -s
