#include "../minishell.h"

void putstr_trim(char *cmd,int end,int begining)
{
    int i;
    int j;
    j = 0;
    i = 0;
    if(end && begining)
        {
            int len = ft_strlen(&cmd[i]);
            //while(cmd[i])
            //{
            //&& cmd[i] != '\"' && cmd[i] != '\''
            write(1,"h",1);
            while(cmd[i] && i < (len - 2) )
            {
               i++;
                write(1,&cmd[i],1);
            }
            //i++;
            //}
        }
    if(end)
        {
         int len = ft_strlen(&cmd[i]);
        while(cmd[i])
            {
            while(cmd[i] && i < (len - 1) && cmd[i] != '\"' && cmd[i] != '\'')
            {
                write(1,&cmd[i],1);
                i++;
            }
                i++;
            }
        }
      if(begining)
        {
            while(cmd[i])
            {
            while(cmd[i] && cmd[i] != '\"' && cmd[i] != '\'')
            {
                //i++;
                write(1,&cmd[i],1);
                i++;
            }
            i++;
            }
        }
    else
        {
            while(cmd[i])
            {
                
                write(1,&cmd[i],1);
                i++;
            }
        }
 }

int quote_there(char c)
{
    if(c == '\'' || c == '\"')
        return(1);
    else
        return(0);
}

void output_echo(char **cmd,int i)
{
    int begining;
    int end;
    begining = quote_there(cmd[i][0]);
        int len = ft_strlen(cmd[i]);
        //I removed backslash zero . end = quote_there(cmd[i][len - 1]);
    end = quote_there(cmd[i][len]);
        putstr_trim(cmd[i],end,begining);
        if(cmd[i + 1])
            write(1," ",1);
}

void echo(char **cmd)
{
    int flag = 0;
    int i = 0;
    if(!cmd[1])
    {
        write(1,"\n",1);
    }
    if(cmd[1][0] == '-' && cmd[1][1] == 'n' && cmd[1][2] == '\0')
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
}