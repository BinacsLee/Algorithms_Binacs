void read(int &x){
    char ch;
    for (ch = getchar(); ch < '0' || ch > '9'; ch = getchar());
    x = 0;
    for (; ch >= '0' && ch <= '9'; ch = getchar())
        x = x * 10 + ch - '0';
}
