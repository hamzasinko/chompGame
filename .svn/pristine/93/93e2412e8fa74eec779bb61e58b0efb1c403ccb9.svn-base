#include <gtk/gtk.h>
#include <stdio.h>
#include "../headers/traitement.h"

#define MATRIX_ROWS 7
#define MATRIX_COLS 9

// Matrix to store the game table
int matrix[MATRIX_ROWS][MATRIX_COLS] = { 
    {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0, 0}
};

// Function prototypes
int compteurCasesValides(int myRow, int myColumn, int mat[MATRIX_ROWS][MATRIX_COLS]);
void modifierMatriceAvecCasesValides(int myRow, int myColumn, int mat[MATRIX_ROWS][MATRIX_COLS]);
void creationTableJeu(GtkWidget *box);

// Function to detach all children from a box
static void detach_all_children(GtkWidget *box) {
    GtkWidget *child = gtk_widget_get_first_child(GTK_WIDGET(box));

    while (child != NULL) {
        GtkWidget *next = gtk_widget_get_next_sibling(child);
        gtk_widget_unparent(child);
        child = next;
    }
}

// Function to quit the game
static void quit_cb(GtkWidget *window) {
    gtk_window_close(GTK_WINDOW(window));
}

// Function to create the game title label
static void CreateLabel(GtkWidget *box) {
    GtkWidget *label;
    label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), "Bienvenue sur le <span foreground=\"#FF0000\"><b>Jeu des carrés</b></span>");
    gtk_box_append(GTK_BOX(box), label);
}

// Function to add the quit button
static void addQuitButton(GtkWidget *box, GtkWidget *window) {
    GtkWidget *quit_button = gtk_button_new_with_label("Quitter la partie");  
    g_signal_connect_swapped(quit_button, "clicked", G_CALLBACK(quit_cb), window);
    gtk_box_append(GTK_BOX(box), quit_button);
}


static void CreateInputText(GtkWidget *box){
    // Create a text input with label and add it to the box
    GtkWidget *label = gtk_label_new("Entrez votre case :");
    gtk_box_append(GTK_BOX(box), label);
    GtkWidget *input = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(input), "A1");
    gtk_box_append(GTK_BOX(box), input);
}

static void AddElementToBox(GtkWidget *box, GtkWidget *window) {
    // add the label for the title
    CreateLabel(box);

    // add the game table
    creationTableJeu(box);

    // add the input text
    CreateInputText(box);

    // add the quit button
    addQuitButton(box, window);
}
// Fonction principale pour obtenir la position et mettre à jour la grille
static void getPosition(GtkWidget *widget, GtkWidget *window, gpointer data) {
    GtkWidget *box = GTK_WIDGET(data);
    GtkWidget *modal_window;
    GtkWidget *content;

    // verify if the parent is a GtkBox
    if (GTK_IS_BOX(box)) { 
        // get the parent of the widget, in this case a GtkGrid
        GtkWidget *parent = gtk_widget_get_parent(widget); 
        // if the parent is a GtkGrid
        if (GTK_IS_GRID(parent)) { 
            gint row, column;

            // get the position of the widget in the grid
            gtk_grid_query_child(GTK_GRID(parent), widget, &column, &row, NULL, NULL);

            // a variable to store the number of valid cases
            int compteurValides = compteurCasesValides(row, column, matrix);

            // if the number of valid cases is less than or equal to 5
            if (compteurValides <= 5) {
                // Change the matrix with the valid cases
                modifierMatriceAvecCasesValides(row, column, matrix);


                // Display a message if the game is over (if the first row and column case is selected)
                if (row == 0 && column == 0) {
                    //open modal window
                    modal_window = gtk_window_new();
                    gtk_window_set_title(GTK_WINDOW(modal_window), "Fin de partie");
                    gtk_window_set_modal(GTK_WINDOW(modal_window), TRUE);
                    
                    // add a size to the modal window
                    gtk_window_set_default_size(GTK_WINDOW(modal_window), 200, 100);

                    // add content to the modal window
                    content = gtk_label_new("Vous avez perdu !");
                    gtk_window_set_child(GTK_WINDOW(modal_window), content);

                    // display the modal window
                    gtk_window_present(GTK_WINDOW(modal_window));
                }

                // Detach all children from the gtk box
                detach_all_children(box);

                // Add the elements to the box
               AddElementToBox(box, window); 

                
            } 
            // Display a message if the number of valid cases is greater than 5
            else {
                //open modal window
                    modal_window = gtk_window_new();
                    gtk_window_set_title(GTK_WINDOW(modal_window), "Erreur");
                    gtk_window_set_modal(GTK_WINDOW(modal_window), TRUE);
                    
                    // add a size to the modal window
                    gtk_window_set_default_size(GTK_WINDOW(modal_window), 200, 100);

                    // add content to the modal window
                    content = gtk_label_new("Il y a plus de 5 cases valides");
                    gtk_window_set_child(GTK_WINDOW(modal_window), content);

                    // display the modal window
                    gtk_window_present(GTK_WINDOW(modal_window));
            }
        } 
        else {
            g_print("Le parent n'est pas une GtkGrid\n");
        }
    } else {
        g_print("Le conteneur n'est pas une GtkBox\n");
    }
}


int compteurCasesValides(int myRow, int myColumn, int mat[MATRIX_ROWS][MATRIX_COLS]) {
    int compteur = 0;
    int i, j;

    for (i = myRow; i < MATRIX_ROWS; i++) {
        if (mat[i][myColumn] == 0) {
            for (j = myColumn; j < MATRIX_COLS; j++) {
                if (mat[i][j] == 0) {
                    compteur++;
                }
            }
        }
    }

    return compteur;
}

void modifierMatriceAvecCasesValides(int myRow, int myColumn, int mat[MATRIX_ROWS][MATRIX_COLS]) {
    int compteur = 0;
    int i, j;

    for (i = myRow; i < MATRIX_ROWS; i++) {
        if (mat[i][myColumn] == 0) {
            for (j = myColumn; j < MATRIX_COLS; j++) {
                if (mat[i][j] == 0) {
                    compteur++;
                    // Modifier l'élément à 1
                    mat[i][j] = 1;
                }
            }
        }
    }
}



// Create the game table
void creationTableJeu(GtkWidget *box) {
    GtkWidget *grid = gtk_grid_new();
    gtk_box_append(GTK_BOX(box), grid);

    // Create and add the game table to the box using the matrix values
    for (int row = 0; row < MATRIX_ROWS; row++) {
        for (int col = 0; col < MATRIX_COLS; col++) {
            GtkWidget *widget;

            // if the value of the matrix is 0, create a button
            if (matrix[row][col] == 0) {
                // Create a gtk button widget with on click event to get the position
                widget = gtk_button_new();
                g_signal_connect(widget, "clicked", G_CALLBACK(getPosition), box); 
            } else {
                // Create a gtk frame widget with a black background
                widget = gtk_frame_new(NULL);
                gtk_widget_set_size_request(widget, 40, 40);  

                // Get the style context of the widget to add the css provider
                GtkStyleContext *context = gtk_widget_get_style_context(widget);
                const char *css = "frame { background-color: black; }";

                // Create a css provider and load the css data
                GtkCssProvider *provider = gtk_css_provider_new();
                gtk_css_provider_load_from_data(provider, css, -1);

                // apply the css provider to the widget
                gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
            }

            // Attach the widget to the grid
            gtk_grid_attach(GTK_GRID(grid), widget, col, row, 1, 1);
        }
    }
}


// Function to create the main window
static void activate(GtkApplication *app, gpointer user_data) {
    // Create the main window
    GtkWidget *window;
    GtkWidget *label;
    GtkWidget *box;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Jeu des carrés");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    // Create a vertical box
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(box, GTK_ALIGN_START);
    gtk_window_set_child(GTK_WINDOW(window), box);
    gtk_box_set_spacing(GTK_BOX(box), 10);  

   // Add the elements to the box
    AddElementToBox(box, window);

    // Display the window
    gtk_widget_show(window);
}

int main(int argc, char *argv[]) {
    // Create a new application
    GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    // Run the application
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
