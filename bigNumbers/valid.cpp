int VerifValid(char s[])
{
    int ok=1;
    unsigned int i;
    for(i=1; i<strlen(s); i++)
        if(!strchr("0123456789",s[i]))
            ok=0;
    if(!strchr("123456789+-",s[0]))
        ok=0;
    if(ok)
        return 1;
    return 0;
}
