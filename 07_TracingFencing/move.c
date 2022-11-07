#include <stdio.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    errno = 0;
    if (argc < 3)
    {
        fprintf(stderr, "Wrong arguments cnt\n");
        return 1;
    }
    FILE* infile;
    FILE* outfile;
    
    char ch;
    
    infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        perror("Error while opening infile");
        return 2;
    }

    outfile = fopen(argv[2], "w");
    if (outfile == NULL)
    {
        fclose(infile);
        perror("Error while opening outfile");
        return 3;
    }
    
    while ((ch = fgetc(infile)) != EOF)
    {
        fputc(ch, outfile);
        if (ferror(outfile))
        {
            fclose(infile);
            fprintf(stderr, "Error while writing to infile");
            return 4;
        }
    }
    
    if (errno)
    {
        fclose(infile);
        fclose(outfile);
        remove(argv[2]);
        fprintf(stderr, "I\\O error:  %d\n", errno);
        return 5;    
    }
        
    if (ferror(infile))
    {
        fclose(outfile);
            
        perror("Error while reading from infile");
        return 6;
    }
        
    if (fclose(infile) == EOF)
    {    
        perror("Error while closing infile");
        remove(argv[2]);
        return 7;
    }
    if (fclose(outfile) == EOF)
    {
        perror("Error while closing outfile");
        remove(argv[2]);
        return 7;
    }
    remove(argv[1]);
    return 0;
}