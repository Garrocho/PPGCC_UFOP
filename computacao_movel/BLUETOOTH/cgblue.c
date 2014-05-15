#include <stdio.h>
#include "cgblue.h"
#include <string.h>
#include <stdlib.h>
#include <obexftp/client.h> 
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>


TipoLista* escanear() {
	inquiry_info *ii = NULL;
    int max_rsp, num_rsp;
    int dev_id, sock, len, flags;
    int i;
    char addr[19] = { 0 };
    char name[248] = { 0 };

    dev_id = hci_get_route(NULL);
    sock = hci_open_dev( dev_id );
    if (dev_id < 0 || sock < 0) {
        perror("opening socket");
        return NULL;
    }

    len  = 8;
    max_rsp = 255;
    flags = IREQ_CACHE_FLUSH;
    ii = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));
    
    num_rsp = hci_inquiry(dev_id, len, max_rsp, NULL, &ii, flags);
    if( num_rsp < 0 ) perror("hci_inquiry");

    TipoLista *lista = (TipoLista*)malloc(sizeof(TipoLista));
    lista->dispositivos = (TipoDispositivo*)malloc(sizeof(TipoDispositivo)*num_rsp);
    lista->tamanho = num_rsp;

    for (i = 0; i < num_rsp; i++) {
        ba2str(&(ii+i)->bdaddr, addr);
        memset(name, 0, sizeof(name));
        if (hci_read_remote_name(sock, &(ii+i)->bdaddr, sizeof(name), 
            name, 0) < 0)
        strcpy(name, "[unknown]");
    	strcpy(lista->dispositivos[i].endereco, addr);
    	strcpy(lista->dispositivos[i].nome, name);
        
    }

    free( ii );
    close( sock );
    return lista;
}

void enviar_arquivo(char *endereco, char *path) {
	char *device = NULL;
	int channel = -1;
	char *filepath, *filename;
	obexftp_client_t *cli = NULL; /*!!!*/
	int ret;

	filepath = path;
	device = endereco;
	channel = obexftp_browse_bt_push(device);

	filename = strrchr(filepath, '/');
	if (!filename)
		filename = filepath;
	else
		filename++;

	cli = obexftp_open(OBEX_TRANS_BLUETOOTH, NULL, NULL, NULL);
	if (cli == NULL) {
		fprintf(stderr, "Error opening obexftp client\n");
		return;
	}

	ret = obexftp_connect_push(cli, device, channel);
	if (ret < 0) {
		fprintf(stderr, "Error connecting to obexftp device\n");
		obexftp_close(cli);
		cli = NULL;
		return;
	}

	ret = obexftp_put_file(cli, filepath, filename);
	if (ret < 0)
		fprintf(stderr, "Error putting file\n");

	ret = obexftp_disconnect(cli);
	if (ret < 0)
		fprintf(stderr, "Error disconnecting the client\n");

	obexftp_close(cli);
	cli = NULL;
}

int main() {
	TipoLista *lista;
	lista = escanear();
	enviar_arquivo(lista->dispositivos[0].endereco, "saida_scan.txt");
	return 0;
}