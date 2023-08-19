#include <gtk/gtk.h>
#include <cstdlib>
#include <ctime>
#include <string>

GtkWidget *entry;
GtkWidget *label;
int targetNumber;

static void checkGuess(GtkWidget *widget, gpointer data) {
    const gchar *text = gtk_entry_get_text(GTK_ENTRY(entry));
    int guess = std::stoi(text);

    std::string message;
    if (guess < targetNumber) {
        message = "Too low!";
    } else if (guess > targetNumber) {
        message = "Too high!";
    } else {
        message = "Correct guess!";
        targetNumber = rand() % 100 + 1; // Generate a new random number
    }

    gtk_label_set_text(GTK_LABEL(label), message.c_str());
    gtk_entry_set_text(GTK_ENTRY(entry), "");
}

int main(int argc, char *argv[]) {
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Number Guessing Game");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), nullptr);

    // Create layout
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), box);

    // Generate a random number
    srand(time(nullptr));
    targetNumber = rand() % 100 + 1;

    // Create entry
    entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box), entry, FALSE, FALSE, 0);

    // Create button
    GtkWidget *button = gtk_button_new_with_label("Check Guess");
    g_signal_connect(button, "clicked", G_CALLBACK(checkGuess), nullptr);
    gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 0);

    // Create label
    label = gtk_label_new("Enter your guess and press 'Check Guess'.");
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);

    // Show all widgets
    gtk_widget_show_all(window);

    // Start the main loop
    gtk_main();

    return 0;
}

