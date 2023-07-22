#include "../minishell.h"
void putstr_trim(char *cmd)
{
    int i = 0;
            while(cmd[i])
            {
                write(1,&cmd[i],1);
                i++;
            }
 }

void output_echo(char **cmd,int i)
{
        putstr_trim(cmd[i]);
        if(cmd[i + 1])
            write(1," ",1);
}

int echo(char **cmd)
{
    int flag = 0;
    int i = 0;
    if(!cmd[1])
    {
        write(1,"\n",1);
    }
    if(cmd[1] && cmd[1][0] == '-' && cmd[1][1] == 'n' && cmd[1][2] == '\0')
        {
            flag = 1;
            ++i;
        }
    while(cmd[++i])
    {
        output_echo(cmd,i);
        if(!cmd[i + 1] && !flag)
            write(1,"\n",1);
    }
    g_exit = EXIT_SUCCESS;
    return(g_exit);
}
