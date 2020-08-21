# Shell Documentation

## General Terms

The following terms may be unclear to readers unfamiliar with ConnectFS, so
please read this section carefully before reading on.

* Operating User - User under whom commands are being executed
    * Affects which database files are read and written, so it is important to ensure you are logged in to the correct operating user before running any commands
* Topic - Graph node with a label that should describe its descendents
* File - Graph node that contains a pointer to a location on the OS' existing file system
* Link - Edge connecting a topic to another topic or a topic to a file
    * Encodes the idea that a topic "contains" its direct file descendents and the file descendents of its topic descendents

## Breakdown of Commands

* who - Displays the name of the current operating user

* use \<username> - Switches operating user to \<username>

* create \<user|topic|file> \<name> \<location> - Creates a user, topic, or file entity with \<name>
    * Creating a file entails providing a \<location> to which the ConnectFS file will point
        * \<location> is the OS file system location at which the "real" file resides

* link \<topic|file> \<child> \<parent> - Generates edge from \<parent> to \<child>
    * \<parent> can be a Topic entity only
    * \<child> can be a Topic entity or a File entity
    
* remove \<user|topic|file> - Removes a user, topic, or file from the graph database
    * Removing a topic or file could force the deletion of edges to which the removed topic/file is party

* show \<users|topics|files> - Displays list of users, topics, or files

* list \<topic> - Lists all topics and files that are descendents of \<topic>

* make \<topic> \<location> - Copies all descendent files of \<topic> into \<location>
    * \<location> is the location of an existing folder on the operating system's file system
    
* exit - Exits out of the shell and shuts down the application




