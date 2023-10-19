import time
import random

COMPCOUNT = 0
CLOCK = 0

def COMPARE(X, Y):
    print("shekhmus")
def swap(A, l, r):
    temp = A[l]
    A[l] = A[r]
    A[r] = temp

def mergesort(array, l, r, n):
#     Mergesort: To sort 𝑛 elements, when 𝑛 ≥ 2, do:
#  Divide the array into two halves;
#  Sort each half recursively;
#  Merge the two sorted halves.

    print(array)

def merge(array, l, r, n):
#     Merge (dtype 𝐴[ ], int 𝑚, dtype 𝐵[ ], int 𝑛, dtype 𝐶[ ]) {
# // Inputs are sorted arrays 𝐴[1: 𝑚] and 𝐵[1: 𝑛]. Output is sorted result 𝐶[1: 𝑚 + 𝑛].
# 𝑖 = 1; //Index into array A
# 𝑗 = 1; //Index into array B
# 𝑘 = 1; //Index into array C
# while (𝑚 ≥ 𝑖 𝑎𝑛𝑑 𝑛 ≥ 𝑗){
# if (𝐴[𝑖] ≤ 𝐵[𝑗])
# { 𝐶[𝑘] = 𝐴[𝑖]; 𝑖 = 𝑖 + 1};
# else
# {𝐶[𝑘] = 𝐵[𝑗]; 𝑗 = 𝑗 + 1};
# 𝑘 = 𝑘 + 1;
# }
# while (𝑚 ≥ 𝑖) //Empty remaining of array A
# { 𝐶[𝑘] = 𝐴[𝑖]; 𝑖 = 𝑖 + 1; 𝑘 = 𝑘 + 1 } ;
# while (𝑛 ≥ 𝑗) //Empty remaining of array B
# {𝐶[𝑘] = 𝐵[𝑗]; 𝑗 = 𝑗 + 1; 𝑘 = 𝑘 + 1};
# }
    print(array)

def pushdown(array, n,  r, i):
#     Algorithm Pushdown (𝐴𝑟𝑟𝑎𝑦 𝐴[ ], 𝑖𝑛𝑡 𝑛, 𝑖𝑛𝑡 𝑟) { // r is root of the subtree to be fixed.
# If (2𝑟 > 𝑛) return; // Already a leaf node.
# // Pick the smaller child 𝑠;
# If (2𝑟 == 𝑛 𝑜𝑟 𝐴[2𝑟] ≤ 𝐴[2𝑟 + 1])
#  𝑠 = 2𝑟
# else 𝑠 = 2𝑟 + 1; // Now 𝑠 is the only child or the smaller child.
# If (𝐴[𝑟] > 𝐴[𝑠]) {
#  Swap (𝐴[𝑟], 𝐴[𝑠]) // Swap with the smaller child
#  Pushdown (𝐴, 𝑛, 𝑠) // Make a recursive call.
# } }
    print(array)

def deleteMax(array, n, r):
#     Algorithm Delete-Min (𝐴𝑟𝑟𝑎𝑦 𝐴[ ],𝐼𝑛𝑡 𝑛){
#  𝑇𝑒𝑚𝑝 = 𝐴[1];
#  𝐴[1] = 𝐴[𝑛]; 𝑛 = 𝑛 − 1;
#  𝑃𝑢𝑠ℎ𝑑𝑜𝑤𝑛(𝐴, 𝑛, 1);
#  𝑅𝑒𝑡𝑢𝑟𝑛(𝑇𝑒𝑚𝑝)}
    print(array)

def buildMaxHeap(array, n):
#     Algorithm Build-Heap (𝑎𝑟𝑟𝑎𝑦 𝐴[ ], 𝑖𝑛𝑡 𝑛) {
# For 𝑖 = ⌊𝑛/2⌋ downto 1 
#  Pushdown (𝐴, 𝑛, 𝑖); }
    print(array)

def heapsort(array, l, r, n):
    print(array)

def quicksort(array, l, r, n):
#     lgorithm Quicksort (𝑎𝑟𝑟𝑎𝑦 𝐴[ ], 𝑖𝑛𝑡 𝑙𝑒𝑓𝑡, 𝑖𝑛𝑡 𝑟𝑖𝑔ℎ𝑡) { //Left and Right indices
# If (𝑙𝑒𝑓𝑡 ≥ 𝑟𝑖𝑔ℎ𝑡) return; // Exit if no remaining elements (if n=1 or n=0)
# 𝑘 = Random (𝑙𝑒𝑓𝑡, 𝑟𝑖𝑔ℎ𝑡); //Pick a random index 
# 𝑉 = 𝐴[𝑘]; //Pick pivot
# swap(𝐴[𝑙𝑒𝑓𝑡], 𝐴[𝑘]); //Put pivot in leftmost spot for now
# 𝑙 = 𝑙𝑒𝑓𝑡 + 1; 𝑟 = 𝑟𝑖𝑔ℎ𝑡;
#  // Inward scan to partition:
# while (𝑙 ≤ 𝑟){ //Continue scan if pointers have not crossed
#  while (𝑙 ≤ 𝑟 𝑎𝑛𝑑 𝐴[𝑙] ≤ 𝑉) 𝑙 = 𝑙 + 1; //Advance left-to-right scan
#  while (𝑙 ≤ 𝑟 𝑎𝑛𝑑 𝐴[𝑟] > 𝑉) 𝑟 = 𝑟 − 1; //Advance right-to-left scan
#  if (𝑙 < 𝑟) { //swap if the pair of pointers did not cross
#  swap(𝐴[𝑙], 𝐴[𝑟]);
#  𝑙 = 𝑙 + 1; 𝑟 = 𝑟 − 1;
#  }
# } 
#  // Finished partitioning when two pointers cross
# Swap (𝐴[𝑙𝑒𝑓𝑡], 𝐴[𝑟]); Swap pivot with rightmost element of left block
# Quicksort(𝐴, 𝑙𝑒𝑓𝑡, 𝑟 − 1);
# Quicksort(𝐴, 𝑟 + 1, 𝑟𝑖𝑔ℎ𝑡);
# } 
    print(array)

def partition(array, l, r, n):
    print(array)