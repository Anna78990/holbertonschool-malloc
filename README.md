<h1><i>_malloc</i> is my original malloc.</h1>
I started this project because I wanted to learn what happens exactly when I use malloc function.
In this library you can use:<br><br>
<ul>
<li><i>_malloc</i>(allocates memory for the bytes passed as arguments)<br></li>
<li><i>_free</i>(free the memory at the address passed as an argument)<br></li>
<li><i>_calloc</i>(allocate a specified amount of memory and then initialize it to zero)<br></li>
<BR>
<h1>Usage:</h1>
The same usage to the original functions.<br>
<ul>
<li><i>_malloc(size_t size)</i></li>
<li><i>_calloc(size_t n_items, size_t size)</i></li>
<li><i>_free(void *ptr)</i></li>
</ul>
<br>
Test:<br>
<img src="https://i.postimg.cc/LXb1q9Yt/Capture-d-e-cran-2023-07-12-a-08-16-48.png"><br>
Output:<br>
<img src="https://i.postimg.cc/d0dsRJxR/Capture-d-e-cran-2023-07-12-a-08-17-13.png">

*_realloc file exists but it does not work well
