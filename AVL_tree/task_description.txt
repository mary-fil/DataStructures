// Part 1 - design a class (complete and fully operational)
//
template <typename Key, typename Info>
class Dictionary { // AVL tree
...	        
};
//
// Part 2 - write an additional (external) function "counter" (not a method)
//
//----------------------------------
Dictionary <string, int>& counter (const string& fileName){
//----------------------------------
//
// the function "counter" creates a Dictionary of words read from a text file 
// (counts word occurrences);
// the Dictionary being created contains all words encountered in the text file 
// together with the word occurrence count, ordered lexically
...
}
//
// Part 3 - write an additional (external) function "listing" (not a method)
//
//----------------------------------
Ring <int, string>& listing (const Dictionary <string, int>&){ 
//----------------------------------
//
// the function "listing" creats a Ring of words from a Dictionary 
// ordered by word occurrence count;
// moreover words with the same counter value should be ordered lexically 
// within the listing
...
}
// --- assumptions ---
// Smith vs smith vs SMITH vs SmItH (different wors)
// Dean vs dean (different wors)
// Lord vs lord (different wors), etc.
