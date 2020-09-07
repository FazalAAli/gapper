## Gapper
#### **G**it **A**uto **P**ull**er**

An easy way to manage your current git repos and automatically keeping them upto date.

#### Note about further updates
I have stopped actively developing this application as it staisfies my needs and the goal I set out for when I created this project.
If there are any glaring security issues or quality of life features, please create a github issue and let me know.
Better yet, in the spirit of why this application was created, give your idea a try and then create a pull request!

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

#### Show all command
Use `gapper -s` to show all repostories in your list. 

#### Verbose tag
Use `-v` whenever you want to see output from the gapper program and from git commands. Otherwise, this will be supressed.

#### Help command
Use `gapper -h` to see a simplified list of all options


[^1]: sudo priveleges are required during installation as the compiled binary is stored in /usr/local/bin 

#### Additional notes:
- You can set up a cronjob or put `gapper -u` in your startup files to update all files when your machine starts
- The config file is stored in your home directory as ".gapperConfig". Uninstalling does not delete the file and it must be manually deleted by user. 

Thank you for viewing my project. I hope it helps you in some manner. If there are any features you'd like added please create an isssue or feel free to submit pull requests. 
