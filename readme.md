## Gapper
#### **G**it **A**uto **P**ull**er**

An easy way to manage your current git repos and automatically keeping them upto date.

### Installation 
1. Clone this library and navigate into it using the terminal
2. Use ` sudo make install ` to install [^1]
3. Now, you're all set to use the `gapper` command from anywhere.
Note: You can use `sudo make uninstall` to uninstall the program but that still leaves the config file in your home directory. 

### Usage

#### Adding a path
To add a path to your list of repos, just use `gapper -p path` where "path" is the path to your dev folder with the .git/ directory.

#### Deleting a path
Similar to adding, you can use the `gapper -d path` to delete the path from your list.

#### Updating all paths.
Use `gapper -u` to update all repositories in your list. This can be used in conjuction with `-p` to update everything after adding a path.

#### Help command
Use `gapper -h` to see a simplified list of all options


[^1]: sudo priveleges are required during installation as the compiled binary is stored in /usr/local/bin 