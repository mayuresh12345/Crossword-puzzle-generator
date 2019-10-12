#include &lt;stdio.h&gt;
#include &quot;mpi.h&quot;
#include &lt;stdlib.h&gt;
#include &lt;string.h&gt;
#include &lt;math.h&gt;
#include &lt;stdbool.h&gt;
#define crossDebug 0

#define value &quot;5&quot;
#define maxfn(x,y) x&gt;y?x:y
#define row atoi(value)
#define max row
#define col row
#define COLOR_RED &quot;\x1b[31m&quot;
#define COLOR_GREEN &quot;\x1b[32m&quot;
#define COLOR_YELLOW &quot;\x1b[33m&quot;
#define COLOR_BLUE &quot;\x1b[34m&quot;
#define COLOR_CYAN &quot;\x1b[36m&quot;
#define COLOR_RESET &quot;\x1b[0m&quot;
int doesSolutionExist = 0;
void getCrosswordMatrix(char arr[row][col]){
printf(&quot;Enter the crossword:\n&quot;);
int ptr=0;
char temp;
do{
scanf(&quot;%&quot;value&quot;s&quot;,arr[ptr++]);
scanf(&quot;%c&quot;,&amp;temp);
}while(ptr&lt;col);
}
void initializeArray(int arr[],int length){
for(int i=0;i&lt;length;i++){
arr[i] = 0;
}
}
void copyArray(int src[],int dest[],int size){
for(int i=0;i&lt;size;i++){
dest[i] = src[i];
}
}
void printCrossword(char arr[row][col]){
if(doesSolutionExist){
printf(COLOR_GREEN &quot;***************\n\n&quot; COLOR_RESET);
printf(COLOR_GREEN &quot;\t\xE2\x9C\x93 Crossword Solution Found:\n\t\t&quot;);
for(int i=0;i&lt;row;i++){
for(int j=0;j&lt;col;j++){
printf(&quot;%2c &quot;,arr[i][j]);
}
printf(&quot;\n\t\t&quot;);
}
printf(COLOR_GREEN &quot;\n*****************\n&quot; COLOR_RESET);
}else {
printf(COLOR_RESET &quot;Crossword =&gt;\n&quot;);
for(int i=0;i&lt;row;i++){
for(int j=0;j&lt;col;j++){
printf(&quot;%c&quot;,arr[i][j]);

}
printf(&quot;\n&quot;);
}
}
}
int getWords(char words[][max+1]){
int size;
printf(&quot;Enter total number of words:\n&quot;);
scanf(&quot;%d&quot;,&amp;size);
printf(&quot;Enter the words:\n&quot;);
for(int i=0;i&lt;size;i++){
scanf(&quot;%s&quot;,words[i]);
}
return size;
}
void printWords(char words[][max+1],int totwords){
if(!crossDebug) return;
printf(&quot;Words =&gt;\n&quot;);
for(int i=0;i&lt;totwords;i++){
printf(&quot;%s\n&quot;,words[i]);
}
}
void calculateWordLengths(char words[][max+1],int wordCount,int wordlen[max+1]){
initializeArray(wordlen,max+1);
for(int i = 0;i &lt; wordCount; i++){
wordlen[strlen(words[i])]++;
}
}
void printWordLength(int wordlen[]){
if(!crossDebug) return;
printf(&quot;Words with length are given:\n&quot;);
for(int i=0;i&lt;max+1;i++){
printf(&quot;For length %d -&gt; %d\n&quot;,i,wordlen[i]);
}
}
void calculateHorizontalCrosswordLengths(char crossword[][max],int horCrosswordlen[max+1]){
initializeArray(horCrosswordlen,max+1);
int ct = 0;
for(int i=0; i &lt; max; i++){
for(int j=0; j&lt;max ;j++){
if(crossword[i][j] == &#39;*&#39;){
if(crossDebug) printf(&quot;Place:&quot;);
horCrosswordlen[ct]++;
if(crossDebug) printf(&quot;HorCrosswordlen[%d] now is

%d\n&quot;,ct,horCrosswordlen[ct]);

ct = 0;
}
else{
if(crossDebug) printf(&quot;Increment\n&quot;);
ct++;
}
}
if(ct != 0){
horCrosswordlen[ct]++;
if(crossDebug) printf(&quot;HorCrosswordlen[%d] now is %d\n&quot;,ct,horCrosswordlen[ct]);
ct = 0;
}
}
horCrosswordlen[0] = 0;
}
void calculateVerticalCrosswordLengths(char crossword[][max],int verCrosswordlen[max+1]){
initializeArray(verCrosswordlen,max+1);
int ct = 0;
for(int i=0; i&lt;max ;i++){
for(int j=0; j&lt;max ;j++){
if(crossDebug) printf(&quot;For %c:&quot;,crossword[i][j]);
if(crossword[j][i] == &#39;*&#39;){
if(crossDebug) printf(&quot;Place:&quot;);
verCrosswordlen[ct]++;
if(crossDebug) printf(&quot;verCrosswordlen[%d] now is

%d\n&quot;,ct,verCrosswordlen[ct]);

ct = 0;
}
else{
if(crossDebug) printf(&quot;Increment\n&quot;);
ct++;
}
}
if(ct != 0){
verCrosswordlen[ct]++;
if(crossDebug) printf(&quot;verCrosswordlen[%d] now is %d\n&quot;,ct,verCrosswordlen[ct]);
ct = 0;
}
}
verCrosswordlen[0] = 0;
}
void printCrosswordLengths(int crosswordLen[max+1]){
if(!crossDebug) return;
printf(&quot;Blanks with length are given:\n&quot;);
for(int i=0;i&lt;max+1;i++){
printf(&quot;For length %d -&gt; %d\n&quot;, i, crosswordLen[i]);
}
}
void calculateHorCrosswordLengthMatrix(int horCrossWordLenMatrix[row][col],char crossword[row][col]){

int cnt=0,ptr=0;
for(int i=0;i&lt;row;i++){
for(int j=0;j&lt;col;j++){
horCrossWordLenMatrix[i][j] = -1;
}
}
for(int i=0;i&lt;row;i++){
ptr = 0;
cnt = 0;
for(int j=0;j&lt;col;j++){
if(crossword[i][j] == &#39;*&#39;){
if(ptr != j){
horCrossWordLenMatrix[i][ptr] = cnt;
}
ptr = j+1;
cnt = 0;
}
else{
cnt++;
}
}
if(cnt!=0){
horCrossWordLenMatrix[i][ptr] = cnt;
}
}
if(crossDebug){
for(int i=0;i&lt;row;i++){
for(int j=0;j&lt;col;j++){
printf(&quot;%2d &quot;,horCrossWordLenMatrix[i][j]);
}
printf(&quot;\n&quot;);
}
}
}
void calculateVerCrosswordLengthMatrix(int verCrossWordLenMatrix[row][col],char crossword[row][col]){
int cnt=0,ptr=0;
for(int i=0;i&lt;row;i++){
for(int j=0;j&lt;col;j++){
verCrossWordLenMatrix[i][j] = -1;
}
}
for(int i=0;i&lt;row;i++){
ptr = 0;
cnt = 0;
for(int j=0;j&lt;col;j++){
if(crossword[j][i] == &#39;*&#39;){
if(ptr != j){
verCrossWordLenMatrix[ptr][i] = cnt;
}

ptr = j+1;
cnt = 0;
}
else{
cnt++;
}
}
if(cnt!=0){
verCrossWordLenMatrix[ptr][i] = cnt;
}
}
if(crossDebug){
for(int i=0;i&lt;row;i++){
for(int j=0;j&lt;col;j++){
printf(&quot;%2d &quot;,verCrossWordLenMatrix[i][j]);
}
printf(&quot;\n&quot;);
}
}
}

int calculateNumberOfProcessRequired(int wordlen[max+1],int crosswordLenArray[max+1]){
int temp1,temp2;
int proc=1;
for(int i=1;i&lt;max+1;i++){
temp1 = crosswordLenArray[i];
temp2 = wordlen[i];
while(temp1 &amp;&amp; temp2){
proc = proc*(temp2);
temp1--;
temp2--;
}
}
return proc;
}
void printProcessCount(char * alignment, int proc){
printf(&quot;The number of %s processes required are %d\n&quot;, alignment, proc);
}
int main(int argc,char **argv){
int rank,size;
MPI_Init(&amp;argc,&amp;argv);
MPI_Comm_rank(MPI_COMM_WORLD,&amp;rank);
MPI_Comm_size(MPI_COMM_WORLD,&amp;size);
//User specified
char crossword[row][col];
int wordcount;
char words[100][max+1]; // initialized to 10words max
//For length

int wordlen[max+1];
int horCrosswordlen[row+1];
int verCrosswordlen[col+1];
int horCrossWordLenMatrix[row][col];
int verCrossWordLenMatrix[row][col];
//For calc processes
int hprocCount,vproc;
//After horizontal
char partiallySolvedCrossword[100][row][col];
int finallySolved[30]; // vproc
int finallyfinallySolved[100][100];
if(rank == 0){
getCrosswordMatrix(crossword);
wordcount = getWords(words);
printf(&quot;-------------\nSolution:\n\n&quot;);
if(crossDebug) {
printCrossword(crossword);
printWords(words,wordcount);
}
//CALCULATE LENGTHS
calculateWordLengths(words,wordcount,wordlen);
printWordLength(wordlen);
calculateHorizontalCrosswordLengths(crossword,horCrosswordlen);
printCrosswordLengths(horCrosswordlen);
calculateHorCrosswordLengthMatrix(horCrossWordLenMatrix,crossword);
//Calculate Processes
hprocCount = calculateNumberOfProcessRequired(wordlen,horCrosswordlen);
printProcessCount(&quot;horizontal&quot;, hprocCount);
}
MPI_Barrier(MPI_COMM_WORLD);
MPI_Bcast(&amp;hprocCount,1,MPI_INT,0,MPI_COMM_WORLD);
MPI_Bcast(crossword,row*col,MPI_CHAR,0,MPI_COMM_WORLD);
MPI_Bcast(words, 100*(max+1), MPI_CHAR, 0, MPI_COMM_WORLD);
MPI_Bcast(wordlen,max+1,MPI_INT,0,MPI_COMM_WORLD);
MPI_Bcast(horCrosswordlen,max+1,MPI_INT,0,MPI_COMM_WORLD);
MPI_Bcast(horCrossWordLenMatrix,row*col,MPI_INT,0,MPI_COMM_WORLD);
MPI_Bcast(&amp;wordcount,1,MPI_INT,0,MPI_COMM_WORLD);
MPI_Barrier(MPI_COMM_WORLD);
int wordsFilled[wordcount];
if(rank &lt; hprocCount){
initializeArray(wordsFilled,wordcount);
int newrank = rank;
int order;

for(int i=1;i&lt;=row;i++){
if(horCrosswordlen[i] == 0 || wordlen[i] == 0)
continue;
int totWords = wordlen[i];
for(int j=0;j&lt;row;j++){
for(int k=0;k&lt;col;k++){
if(horCrossWordLenMatrix[j][k] == i){
order = newrank%totWords;
newrank = newrank/totWords;
totWords--;
for(int l=0;l&lt;wordcount;l++){
if(strlen(words[l]) == i &amp;&amp; wordsFilled[l] == 0){
if(order){
order--;
continue;
}
for(int m=0;m&lt;strlen(words[l]);m++){
crossword[j][k+m] =

words[l][m];

}
wordsFilled[l] = 1;
break;
}
}
}
}
}
}
}
MPI_Barrier(MPI_COMM_WORLD);
int wordUsageFlag[100][wordcount];

MPI_Gather(crossword,row*col,MPI_CHAR,partiallySolvedCrossword,row*col,MPI_CHAR,0,MPI_COMM_WORLD);
MPI_Gather(wordsFilled,wordcount,MPI_INT,wordUsageFlag,wordcount,MPI_INT,0,MPI_COMM_WORLD);
MPI_Barrier(MPI_COMM_WORLD);
if(rank == 0){
for(int i=0;i&lt;hprocCount;i++){
if(!crossDebug) break;
printCrossword(partiallySolvedCrossword[i]);
}
calculateVerticalCrosswordLengths(crossword,verCrosswordlen);
printCrosswordLengths(verCrosswordlen);

calculateVerCrosswordLengthMatrix(verCrossWordLenMatrix,crossword);
//Calculate Processes
vproc = calculateNumberOfProcessRequired(wordlen,verCrosswordlen);
printProcessCount(&quot;vertical&quot;, vproc);
}
MPI_Barrier(MPI_COMM_WORLD);
MPI_Bcast(partiallySolvedCrossword,hprocCount*row*col,MPI_CHAR,0,MPI_COMM_WORLD);
MPI_Bcast(&amp;vproc,1,MPI_INT,0,MPI_COMM_WORLD);
MPI_Bcast(wordUsageFlag,hprocCount*wordcount,MPI_INT,0,MPI_COMM_WORLD);
MPI_Bcast(&amp;vproc,1,MPI_INT,0,MPI_COMM_WORLD);
MPI_Bcast(verCrosswordlen,max+1,MPI_INT,0,MPI_COMM_WORLD);
MPI_Bcast(verCrossWordLenMatrix,row*col,MPI_INT,0,MPI_COMM_WORLD);
// MPI_Barrier(MPI_COMM_WORLD);
if(rank &lt; vproc){
finallySolved[rank] = 0;
for(int hprocIndex = 0; hprocIndex &lt; hprocCount; hprocIndex++){
int newrank = rank;
int order;
bool flag = false;
for(int i=1;i&lt;=row;i++){
if(verCrosswordlen[i] == 0 || wordlen[i] == 0)
continue;
int totWords = wordlen[i];
for(int j=0;j&lt;row;j++){
for(int k=0;k&lt;col;k++){
if(verCrossWordLenMatrix[j][k] == i){
order = newrank%totWords;
newrank = newrank/totWords;
totWords--;
for(int l=0;l&lt;wordcount;l++){
if(strlen(words[l]) == i &amp;&amp;

wordUsageFlag[hprocIndex][l] == 0){

if(order){
order--;
continue;
}
for(int

m=0;m&lt;strlen(words[l]);m++){

if((partiallySolvedCrossword[hprocIndex][j+m][k] == &#39;#&#39;) || (partiallySolvedCrossword[hprocIndex][j+m][k]
== words[l][m])){
partiallySolvedCrossword[hprocIndex][j+m][k] = words[l][m];

}
else{
flag =

true;

break;
}
}

wordUsageFlag[hprocIndex][l] = 1;

break;
}
if(flag)
break;

}
if(flag)
break;

}
}
if(flag)
break;

}
if(flag)
break;

}
if(!flag){
int isSolutionCheck=0;
for(int wordIndex=0; wordIndex&lt;wordcount; wordIndex++){
isSolutionCheck = isSolutionCheck +

wordUsageFlag[hprocIndex][wordIndex];
}
if(crossDebug &amp;&amp; wordcount != isSolutionCheck){
printf(&quot;For rank %d-&gt;\n&quot;,rank);
printCrossword(partiallySolvedCrossword[hprocIndex]);
};
if(isSolutionCheck == wordcount){
doesSolutionExist = 1;
MPI_Bcast(&amp;doesSolutionExist,1,MPI_INT,rank,MPI_COMM_WORLD);
printf(&quot;Rank %d\t\n&quot;,rank);
printCrossword(partiallySolvedCrossword[hprocIndex]);
printf(&quot;\n&quot;);
}
finallySolved[hprocIndex] = 1;
break;
}
}
}
MPI_Barrier(MPI_COMM_WORLD);

MPI_Gather(crossword,row*col,MPI_CHAR,partiallySolvedCrossword,row*col,MPI_CHAR,0,MPI_COMM_WORLD);
MPI_Gather(finallySolved,vproc,MPI_INT,finallyfinallySolved,vproc,MPI_INT,0,MPI_COMM_WORLD);
MPI_Barrier(MPI_COMM_WORLD);
printf(&quot;rank %d\n&quot;, rank);
MPI_Finalize();
if(!doesSolutionExist){
printf(COLOR_RED &quot;***************\n&quot; COLOR_RESET);
printf(COLOR_RED &quot;No Solution for Crossword Found\n&quot; COLOR_RESET);
printf(COLOR_RED &quot;***************\n\n&quot; COLOR_RESET);
}
return 1;
}