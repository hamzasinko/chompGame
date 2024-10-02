#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include "../headers/matrice.h"
#include "../headers/traitement.h"
#include "../headers/interaction.h"
#include "../headers/const.h"
#include "../headers/ai.h"
#include "../headers/network.h"
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define BUFSIZE 4096
extern int errno;

/*
* Global matrix
*/
int M[7][9];  
int INDEX[2] = {-1, -1};

int sock;
int server_sock;
struct sockaddr_in server;
const char *default_ip = "127.0.0.1";
unsigned short default_port = 5555; 
gchar buffer[BUFSIZE];
GtkWidget *entry_msg;  
GtkWidget *buttons[7][9]; 

GtkWidget *status_label;
    
/*
* Initialize scores for AI
*/
Scores score;

int result;

int networkAble = 1;

/*
* Avoid AI playing against itself since network is non-blocking
*/
int ai_waiting_for_response = 1;

void error(const char *msg) {
    perror(msg);
    exit(1);
}

/*
* Update player last move on the GUI
*/
void update_status_label(const gchar *new_text) {
    gtk_label_set_text(GTK_LABEL(status_label), new_text);
}

/*
* Displays a pop-up with the chosen message
*/
void afficher_popup(const gchar *contenu) {

    GtkWidget *popup = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(popup), "Notification");
    gtk_window_set_default_size(GTK_WINDOW(popup), 300, 200);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(popup), vbox);

    GtkWidget *label = gtk_label_new(contenu);
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 5);

    GtkWidget *button_close = gtk_button_new_with_label("Fermer");
    gtk_box_pack_start(GTK_BOX(vbox), button_close, FALSE, FALSE, 5);
    
    /*
    * Button with signal callback to close the pop-up
    */
    g_signal_connect(button_close, "clicked", G_CALLBACK(gtk_window_close), popup);

    gtk_widget_show_all(popup);

    gtk_window_present(GTK_WINDOW(popup));
}

/*
* Set score at zero once to make AI work
*/
void init_scores() {
    score.score_p1 = 0;
    score.score_p2 = 0;
}

/*
* Send a message to the remote host
*/
void send_message(const gchar *msg) {
    int n = send(sock, msg, strlen(msg), 0);
    if (n < 0) {
        error("Erreur lors de l'envoi du message");
    }
}

/*
* CHeck if provided port is a valid one
*/
int is_valid_port(const char *str) {
    while (*str) {
        if (*str < '0' || *str > '9') {
            return 0;
        }
        str++;
    }
    return 1;
}


/*
* Check if input string is a valid ip:port
*/
int parse_ip_port(const char *str, char *ip, char *port) {
    const char *colon_pos = strchr(str, ':');
    if (colon_pos == NULL) {
        return 0;
    }

    size_t ip_length = colon_pos - str;
    strncpy(ip, str, ip_length);
    ip[ip_length] = '\0';  

    strcpy(port, colon_pos + 1);  

    return is_valid_port(port);
}

/*
* Convert A1 coordinate to 0;0, for example
*/
void notationToIndex(const char* notation, int* x, int* y) {

    /*
    * Put first character into uppercase
    */
    char ligne = toupper(notation[0]);
    
/*
* Actually convert into coordinates
*/
    *x = ligne - 'A';
    *y = notation[1] - '1';
}


/*
* Print commands usage
*/
void print_usage() {
    printf("Usage:\n");
    printf("./game -s -ia <port>\n");
    printf("./game -c -ia <@IP>:<port>\n");
    printf("./game -c <@IP>:<port>\n");
    printf("./game -s <port>\n");
    printf("./game -l\n");
}

/*
* Updates matrix state
*/
void update_buttons_from_matrix() {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 9; j++) {
            /*
            * Turn palyed buttons into read-only
            */
            if (M[i][j] == 0) {
                gtk_widget_set_sensitive(buttons[i][j], TRUE);
                gtk_button_set_label(GTK_BUTTON(buttons[i][j]), " ");
            } else {
                gtk_widget_set_sensitive(buttons[i][j], FALSE);
                gtk_button_set_label(GTK_BUTTON(buttons[i][j]), "X");
            }
        }
    }
}

/*
* Print commands usage
*/
void on_button_clicked(GtkWidget *widget, gpointer data) {
    int *coords = (int *)data;
    char status_msg[100];
    
    /*
    * COnvert clicked button into their A1, A2 ... coordinates
    */
    gchar coord_msg[50];
    gchar lettre_colonne = 'A' + coords[1];
    int ligne = coords[0] + 1;
    
    snprintf(coord_msg, sizeof(coord_msg), "%c%d\n", lettre_colonne, ligne);
    coord_msg[0] = toupper(coord_msg[0]);

    int x, y;
    
    notationToIndex(coord_msg, &x, &y);
    
    
    /*
    * CHeck if matrix is valid without updating it
    */
    if (verifierValiditeCaseAi(y, x, M)){
    printf("LA case est valide");
    
        do {

        INDEX[0] = -1;
        INDEX[1] = -1;
        miseAJourParReseau(coord_msg, INDEX);
    } while (!verifierValiditeCase(INDEX[0], INDEX[1], M));

    /*
    * Update buttons accordingly
    */
    update_buttons_from_matrix();

    if (coupPerdant(coord_msg)){
        printf("Perdu");
        afficher_popup("Vous avez perdu!");
    }

    if (networkAble){
    /*
    * Send move to server
    */
    send_message(coord_msg);
    }
    
    printf("%s", coord_msg);
    
    sprintf(status_msg, "Vous avez joué %s", coord_msg);
    update_status_label(status_msg);
    }else{
    printf("La case n'est pas valide");
    afficher_popup("Case invalide");
    }
    

}

/*
* Callback function for typed coordinates from the text field
*/
void on_send_button_clicked(GtkWidget *widget, gpointer data) {
    const gchar *msg = gtk_entry_get_text(GTK_ENTRY(entry_msg));
    int x, y;
    
    char status_msg[100];
        
    notationToIndex(msg, &x, &y);
    
    /*
    * Check if matrix is valid before updating it
    */
    if (verifierValiditeCaseAi(y, x, M)){
    printf("LA case est valide");
    
    do {
        INDEX[0] = -1;
        INDEX[1] = -1;
        miseAJourParReseau((char *)msg, INDEX);
    } while (!verifierValiditeCase(INDEX[0], INDEX[1], M));

    /*
    * Update buttons from matrix
    */
    update_buttons_from_matrix();
    /*
    * Send move to remote host
    */
    if (coupPerdant(msg)){
                printf("Perdu");
        afficher_popup("Vous avez perdu!");
    }
        if (networkAble){
    send_message(msg);
        }
        
    sprintf(status_msg, "Vous avez joué %s", msg);
    update_status_label(status_msg);
    
    /*
    * Clear text field after sending move
    */
    gtk_entry_set_text(GTK_ENTRY(entry_msg), "");
    }else{
    printf("LA case n'est pas valide");
    afficher_popup("Case invalide");
    }
}

/*
* Non-blocking function to recieve messages
*/
gboolean receive_message(gpointer data) {
    char recv_buffer[BUFSIZE];
    int n = recv(sock, recv_buffer, BUFSIZE - 1, 0);
    char status_msg[100];
    
    if (n > 0) {
        recv_buffer[n] = '\0';
        printf("Message from server: %s\n", recv_buffer);
        
        do {
            INDEX[0] = -1;
            INDEX[1] = -1;
            miseAJourParReseau(recv_buffer, INDEX);
        } while (!verifierValiditeCase(INDEX[0], INDEX[1], M));
        
        update_buttons_from_matrix();

        if (coupPerdant(recv_buffer)){
                    printf("Gagné");
        afficher_popup("Vous avez gagné !");
            }
            
            /*
            * Update label accordingly
            */
    sprintf(status_msg, "Adversaire a joué %s", recv_buffer);
    update_status_label(status_msg);
    
      /*
      * Disconnect if any errors
      */
    } else if (n == 0) {
        printf("Connexion fermée par le serveur\n");
        return FALSE;
    } else if (n < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
    
        perror("Erreur lors de la réception des données");
        return FALSE; 
    }
    /*
    * Continue listening for messages
    */
    return TRUE; 
}


/*
* Recieve a message and send an AI generated response
*/
gboolean receive_message_respond_AI(gpointer data) {

    char status_msg[100];
    char recv_buffer[BUFSIZE];
    char move[3];
    int n = recv(sock, recv_buffer, BUFSIZE - 1, 0);
    
    if (n > 0) {
        recv_buffer[n] = '\0';
        printf("Message from server: %s\n", recv_buffer);
        
        do {
            INDEX[0] = -1;
            INDEX[1] = -1;
            miseAJourParReseau(recv_buffer, INDEX);
        } while (!verifierValiditeCase(INDEX[0], INDEX[1], M));
        
        update_buttons_from_matrix();
                if (coupPerdant(recv_buffer)){
        afficher_popup("Vous avez gagné !");
            }
        
          /*
          * Update label accoringly
          */
        sprintf(status_msg, "Adversaire a joué %s", recv_buffer);
        update_status_label(status_msg);
        
        /*
        * If a message is recieved, let AI play by minimizing opponent score
        */
        bzero(move, 3);
        aiMoveV1Min(M, move, &score);
        
            do {
            INDEX[0] = -1;
            INDEX[1] = -1;
            miseAJourParReseau(move, INDEX);
        } while (!verifierValiditeCase(INDEX[0], INDEX[1], M));

                if (coupPerdant(move)){
                            printf("GAgné");
        afficher_popup("AI a gagné!");
            }

        /*
        * Update buttons and label
        */

        update_buttons_from_matrix();
        send_message(move);
        sprintf(status_msg, "IA a joué %s", move);
        update_status_label(status_msg);
        
        
    } 
          /*
      * Disconnect if any errors
      */
    else if (n == 0) {
        printf("Connexion fermée par le serveur\n");
        return FALSE;  
    } else if (n < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {

        perror("Erreur lors de la réception des données");
        return FALSE;
    }
    
    return TRUE; 
}


/*
* Make AI play first move
*/
gboolean send_message_AI(gpointer data) {
    char status_msg[100];
    char recv_buffer[BUFSIZE];
    char move[3];
    if (ai_waiting_for_response) {
        bzero(move, 3);
        aiMoveV1Max(M, move, &score);
        
            do {
            INDEX[0] = -1;
            INDEX[1] = -1;
            miseAJourParReseau(move, INDEX);
        } while (!verifierValiditeCase(INDEX[0], INDEX[1], M));
        update_buttons_from_matrix();

                        if (coupPerdant(move)){
                            printf("Perdu");
        afficher_popup("AI a perdu!");
            }

        send_message(move);
        
        sprintf(status_msg, "IA a joué %s", move);
        update_status_label(status_msg);
        
        ai_waiting_for_response = 0;
        printf("AI a joué");
            
    }else {
    int n = recv(sock, recv_buffer, BUFSIZE - 1, 0);
    if (n > 0) {
        recv_buffer[n] = '\0';
        printf("Message from server: %s\n", recv_buffer);
        
        do {
            INDEX[0] = -1;
            INDEX[1] = -1;
            miseAJourParReseau(recv_buffer, INDEX);
        } while (!verifierValiditeCase(INDEX[0], INDEX[1], M));
        
        if (coupPerdant(recv_buffer)){
        printf("Gagné");
        afficher_popup("AI a gagné!");
        }


        update_buttons_from_matrix();
        
        sprintf(status_msg, "Adversaire a joué %s", recv_buffer);
        update_status_label(status_msg);
        
        ai_waiting_for_response = 1;
        }
      /*
      * Disconnect if any errors
      */
        else if (n == 0) {
        printf("Connexion fermée par le serveur\n");
        return FALSE;
    } else if (n < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
        perror("Erreur lors de la réception des données");
        return FALSE;
    }
    
    return TRUE;
      /*
      * Continue
      */
}
}


/*
* MAin function to start the program
*/
int main(int argc, char *argv[]) {
    char input[2];
    remplissage(M); 
    
    init_scores();
/*
* GTK init
*/
    gtk_init(&argc, &argv);
    
    if (argc == 4 && strcmp(argv[1], "-s") == 0 && strcmp(argv[2], "-ia") == 0) {
      /*
      * ./main -s -ia <port>
      */
        if (is_valid_port(argv[3])) {
        
        
            printf("Mode serveur avec IA sur le port: %s\n", argv[3]);
            
            //server_sock = initServerSocket(default_port);
            
            server_sock = initServerSocket(atoi(argv[3]));
            if (server_sock == -1) {
                printf("Échec de l'initialisation du serveur\n");
                return 1;
            }

              /*
              * Accept an incomming connexion
              */
            sock = accepterClient(server_sock);
            if (sock == -1) {
                printf("Échec de la connexion avec le client\n");
                close(server_sock);
                return 1;
            }
            g_idle_add(receive_message_respond_AI, NULL);
            
            
        } else {
            printf("Port invalide: %s\n", argv[3]);
            print_usage();
        }

    } else if (argc == 4 && strcmp(argv[1], "-c") == 0 && strcmp(argv[2], "-ia") == 0) {
      /*
      * ./main -c -ia <@IP>:<port>
      */ 
        char ip[50], port[10];
        if (parse_ip_port(argv[3], ip, port)) {
        
        
            printf("Mode client avec IA connecté à IP: %s et port: %s\n", ip, port);
            sock = initClientSocket(ip, atoi(port));
            if (sock == -1) {
                printf("Échec de la connexion au serveur\n");
                return 1;
            }
            g_idle_add(send_message_AI, NULL);
            
            
        } else {
            printf("Adresse IP ou port invalide: %s\n", argv[3]);
            print_usage();
        }

    } else if (argc == 3 && strcmp(argv[1], "-c") == 0) {
          /*
      * ./main -c <@IP>:<port>
      */ 
        char ip[50], port[10];
        if (parse_ip_port(argv[2], ip, port)) {
    
        
            printf("Mode client connecté à IP: %s et port: %s\n", ip, port);
            sock = initClientSocket(ip, atoi(port));
            if (sock == -1) {
                printf("Échec de la connexion au serveur\n");
                return 1;
            }
    
            g_idle_add(receive_message, NULL);
            
            
            } else {
                printf("Adresse IP ou port invalide: %s\n", argv[2]);
                print_usage();
            }



    } else if (argc == 3 && strcmp(argv[1], "-s") == 0) {
              /*
      * ./main -s <port>
      */ 
        if (is_valid_port(argv[2])) {
        
        
            printf("Mode serveur sur le port: %s\n", argv[2]);
                               
            server_sock = initServerSocket(atoi(argv[2]));
            if (server_sock == -1) {
                printf("Échec de l'initialisation du serveur\n");
                return 1;
            }

            /*
            * Accept a client connection
            */ 
            sock = accepterClient(server_sock);
            if (sock == -1) {
                printf("Échec de la connexion avec le client\n");
                close(server_sock);
                return 1;
            }
            
            g_idle_add(receive_message, NULL);
            
            
        } else {
            printf("Port invalide: %s\n", argv[2]);
            print_usage();
        }

    } else if (argc == 2 && strcmp(argv[1], "-l") == 0) {
                /*
            * ./main -l
            */ 
        printf("Mode local activé\n");
        networkAble = 0;

    } else {
            /*
            * Exit program if no valid args are found
            */ 
        printf("Erreur: format de commande invalide\n");
        print_usage();
        exit(1);
    }

 GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Chomp Game");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

                /*
            * GTKheader for modern look
            */ 
    GtkHeaderBar *header_bar = GTK_HEADER_BAR(gtk_header_bar_new());
    gtk_header_bar_set_title(header_bar, "Chomp Game");
    gtk_header_bar_set_subtitle(header_bar, "Avoid A1 at any cost !");
    gtk_header_bar_set_show_close_button(header_bar, TRUE);
    gtk_window_set_titlebar(GTK_WINDOW(window), GTK_WIDGET(header_bar));

                /*
            * Vertical box to organize widgets
            */ 
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

                /*
            * Grid for buttons
            */ 
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 10);

                /*
            * Columns labels
            */ 
    for (int j = 0; j < 9; j++) {
        GtkWidget *label = gtk_label_new(NULL);
        gchar label_text[2] = {'A' + j, '\0'};
        gtk_label_set_text(GTK_LABEL(label), label_text);
        gtk_grid_attach(GTK_GRID(grid), label, j + 1, 0, 1, 1);
    }

            /*
            * Labels for rows
            */ 
    for (int i = 0; i < 7; i++) {
        GtkWidget *label = gtk_label_new(NULL);
        gchar label_text[3];
        snprintf(label_text, sizeof(label_text), "%d", i + 1);
        gtk_label_set_text(GTK_LABEL(label), label_text);
        gtk_grid_attach(GTK_GRID(grid), label, 0, i + 1, 1, 1);

        for (int j = 0; j < 9; j++) {
                        /*
            * Create every buttons
            */ 
            buttons[i][j] = gtk_button_new_with_label(" ");
            gtk_widget_set_size_request(buttons[i][j], 50, 50);
            gtk_widget_set_margin_start(buttons[i][j], 2);
            gtk_widget_set_margin_end(buttons[i][j], 2);
            gtk_widget_set_margin_top(buttons[i][j], 2);
            gtk_widget_set_margin_bottom(buttons[i][j], 2);

                        /*
            * Allocate memory
            */ 
            int *coords = g_new(int, 2);
            coords[0] = i;
            coords[1] = j;

                        /*
            * Callback for every buttons
            */ 
            g_signal_connect(buttons[i][j], "clicked", G_CALLBACK(on_button_clicked), coords);

                        /*
            * Add button to grid
            */ 
            gtk_grid_attach(GTK_GRID(grid), buttons[i][j], j + 1, i + 1, 1, 1);
        }
    }

                /*
            * Horizontal box for button
            */ 
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 10);

                /*
            * Button to send move
            */ 
    GtkWidget *send_button = gtk_button_new_with_label("Envoyer message");
    gtk_box_pack_start(GTK_BOX(hbox), send_button, FALSE, FALSE, 10);
    g_signal_connect(send_button, "clicked", G_CALLBACK(on_send_button_clicked), NULL);

                /*
            * Text field
            */ 
    entry_msg = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_msg), "Entrez votre message...");
    gtk_box_pack_start(GTK_BOX(hbox), entry_msg, TRUE, TRUE, 10);

                /*
            * Status label
            */ 
    status_label = gtk_label_new("En attente");
    gtk_box_pack_start(GTK_BOX(vbox), status_label, FALSE, FALSE, 10);

    fcntl(sock, F_SETFL, O_NONBLOCK);
    gtk_widget_show_all(window);

                /*
            * Handle window close button
            */ 
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

                /*
            * Main GTK loop
            */ 
    gtk_main();

                /*
            * Close socket at game over
            */ 
    close(sock);
                /*
            * Initialize buttons with empty matrix
            */ 
    update_buttons_from_matrix();

    return 0;
}

