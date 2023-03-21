#include <iostream>           // ci serve per stampare a video il testo
//#include <TGraphErrors.h>     // ci serve per istanziare grafici
//#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
//#include <TCanvas.h>          // ci serve per disegnare i grafici
//#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include <iomanip>            // ci serve per manipolare l'output a video
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


using namespace std;

/*void passaAlto(){

float

}*/

const char* getfield(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, ",");
            tok && *tok;
            tok = strtok(NULL, ";\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

int fitVWork(){

    float HV_work[9];
    float err_HV_work[9]; //1%+-5V
    float eff[9];
    float err_eff[9];

    FILE* stream=fopen("BB8_PassaAlto.csv", "r");
    if(stream==NULL){
            cout << "fallito"<<endl;
            return 1;}

    char line[1024];
    int i=0;
    while (fgets(line, 1024, stream))
    {
        //char* tmp[1024];
        //strcpy(tmp,stream);
        HV_work[i]=stod(getfield(stream, 1));
        err_HV_work[i]=stod(getfield(stream, 2));
        eff[i]=stof(getfield(stream, 3));
        err_eff[i]=stod(getfield(stream, 4));
        cout << HV_work[i]<<" "<<err_HV_work[i]<<" "<< eff[i]<< " "<< err_eff[i]);
        // NOTE strtok clobbers stream
        //free(stream);
        i++;
    }
    fclose(stream);
    return 0;

}

