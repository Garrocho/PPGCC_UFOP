#ifndef CGBLUE_H
#define CGBLUE_H

typedef struct dipositivo {
	char nome[50];
	char endereco[50];
}TipoDispositivo;

typedef struct lista {
	int tamanho;
	TipoDispositivo *dispositivos;
}TipoLista;

TipoLista* escanear();

void enviar_arquivo(char *endereco, char *path);

#endif /* CGBLUE_H */