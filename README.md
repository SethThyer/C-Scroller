# C-Scroller
A simple, bloat-less text scroller. 

## Example
```
input: echo "scrolling this" | scroll
output:     "scrolling this # "

input: echo "scrolling this" | scroll
output:     " scrolling this #"

input: echo "scrolling this" | scroll
output:     "# scrolling this "

ect...
```
<br/><br/>
- Always maintains size by using whitespaces
- Centers text & doesn't scroll if it fits within the scroll area
- Works with DWM-blocks
<br/>
<br/>
#### ToDo
[ ] Work with UTF-16 characters.
[ ] Create a Makefile
