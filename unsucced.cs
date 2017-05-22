using System;
using System.Collections.Generic;
using System.Linq;
public class Program {
    static Dictionary<long, long> dic;
    static void Input() {
        int nub = int.Parse(Console.ReadLine());
        dic = new Dictionary<long,long>(nub * 2);
        for (int i = 0; i < nub; i++) {
            string[] s = Console.ReadLine().Split(' ');
            for (int j = 0; j < s.Length; j++) {
                long temp = long.Parse(s[j]);
                if (dic.ContainsKey(temp)) dic[temp]++;
                else dic.Add(temp, 1);
            }
        }
    }
    static void Main(string[] args) {
        Input();
        var a = new Dictionary<long, long>();
        foreach (var item in dic) {
           long MaxTime = 2;
            if(item.Value>=MaxTime) {
                if (item.Value > MaxTime) {
                    a.Clear();
                    MaxTime = item.Value;
                }
                a.Add(item.Key, item.Value);
            }
        }
        var b = a.First();
        foreach (var item in a) {
            if (b.Key > item.Key) b = item;
        }
        Console.Write(b.Key + " " + b.Value);
        if (a.Count > 1) Console.WriteLine(" "+a.Count);
        else Console.WriteLine();
    }
}
