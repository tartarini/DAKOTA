file(READ "${infile}" contents)
file(READ "${datefile}" date)
string(STRIP ${date} date)
set(append-line "#define NSPEC_DATE \"${date}\"\n")
file(WRITE "${outfile}" "${contents}")
file(APPEND "${outfile}" "${append-line}")
file(REMOVE "${infile}")
file(REMOVE "${datefile}")
