#define IDXTYPE int
#define FOR(idxName,start,end,step) for(IDXTYPE idxName=start;idxName<end;idxName+=step)
#define FORI(idxName,end) for(IDXTYPE idxName=0;idxName<end;idxName++)
#define FORR(idxName,start) for(IDXTYPE idxName=start;idxName>=0;idxName--)
#define CONT_RANGE(c) c.begin(),c.end()
#define RANGE(first,advanceSize) first,first+advanceSize 
template<typename C, typename T>
bool IsIn(const T& key, const C& c) { return c.find(key) != c.end(); }
typedef vector<int> VecInt;
