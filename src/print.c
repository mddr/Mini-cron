
void PrintUsage()
{
    printf("Demon uruchamiany jest w następujący sposób:\n");
    printf("./minicron <taskfile> <outfile>\n");
    printf("Plik taskfile zawiera zadania zapisane w następującym formacie:/n");
    printf("<hour>:<minutes>:<command>:<info>\n");
    printf("Przy czym command jest dowolnym programem.\n");
    printf("Parametr info może mieć jedną z trzech wartości:\n");
    printf("\t– 0 – użytkownik chce otrzymać treść, jaką polecenie wypisało na standardowe wyjście (stdout)\n");
    printf("\t– 1 - użytkownik chce otrzymać treść, jaką polecenie wypisało na wyjście błędów (stderr)\n");
    printf("\t– 2 – użytkownik chce otrzymać treść, jaką polecenie wypisało na standardowe wyjście i wyjście błędów\n");
}