using System;
using static System.Console;
public sealed class Program {
    static void Swap(ref int a,ref int b) {
        int c = a;
        a = b;
        b = c;
    }
    static void Heap_Sort(int[] a) {
        int N = a.Length;
        void swim(int i)
        {
            while (i>1&&a[i]>a[(i-1)/2]) {
                Swap(ref a[i], ref a[(i - 1) / 2]);
                i /= 2;
            }
        }
        void sink(int k)
        {
            while (2*k+1<N) {
                int j = 2 * k+1;
                if (j < N - 1&&a[j]<a[j+1]) j++;
                if (a[j] < a[k]) break;
                Swap(ref a[j], ref a[k]);
                k = j;
            }
        }
        for (int i = (N-1)/2; i>=0; i--) sink(i);//Build Heap
        while (N > 0) {
            Swap(ref a[0], ref a[N-- - 1]);
            sink(0);
        }//exchange the index 0 and the max index of the array
    }
    static void Shell_Sort(int[] a) {
        int h = 1;
        while (h<a.Length/3) {
            h =h* 3 + 1;
        }
        while (h>0) {
            for (int i = h; i < a.Length; i++) {
                for (int j = i; j >=h&&a[j]<a[j-h]; j-=h) {
                    Swap(ref a[j], ref a[j - h]);
                }
            }
            h /= 3;
        }
    }
    static void Insertion_Sort(int[] a) {
        for (int i = 1; i < a.Length; i++) {
            for (int j = i; j >0&&a[j]<a[j-1]; j--) {
                Swap(ref a[j],ref a[j - 1]);
            }
        }
    }
    static void Insertion_Sort(int[] a,int start,int end) {
        for (int i = start; i <= end; i++) {
            for (int j = i; j > start && a[j] < a[j - 1]; j--) {
                Swap(ref a[j], ref a[j - 1]);
            }
        }
    }
    static void Bubble_Sort(int[] a) {
        for (int i = 0; i < a.Length; i++) {
            Boolean IsSwaped = false;
            for (int j=0; j<a.Length-1;j++) {
                if (a[j] > a[j + 1]) {
                    Swap(ref a[j], ref a[j + 1]);
                    IsSwaped = true;
                }
            }
            if (!IsSwaped) break;
        }
    }
    static void Merge_Sort(int[] a) {
        int[] aux = new int[a.Length];
        void Sort(int start,int end)
        {
            if (end <= start) return;
            int middle = (start + end) / 2;
            void Merge()
            {
                int leftIndex = start, rightIndex = middle + 1,auxIndex=start;
                while (leftIndex<=middle&&rightIndex<=end) {
                    if (a[leftIndex] < a[rightIndex]) aux[auxIndex++] = a[leftIndex++];
                    else aux[auxIndex++] = a[rightIndex++];    
                }
                while (leftIndex<=middle) aux[auxIndex++] = a[leftIndex++];
                while (rightIndex<=end) aux[auxIndex++] = a[rightIndex++];
                for (int i = start; i < end+1; i++) a[i] = aux[i];
            }
            Sort(start, middle);
            Sort(middle + 1, end);
            Merge();
        }
        Sort(0, a.Length - 1);
    }
    static void Main(string[] args) {
        int[] a = new int[101];
        for (int i = 0; i < 101; i++) {
            a[i]=((int)Math.Pow(-i, i % 3));
        }
        Heap_Sort(a);
        foreach (var item in a) {
            Write(item + " ");
        }
    }
}
