using System;
using System.Collections.Generic;
using System.Linq;
public class Program {
    static Dictionary<string, int> dic;
    static void Input() {
        int nub = int.Parse(Console.ReadLine());
        dic = new Dictionary<string,int>(nub * 2);
        for (int i = 0; i < nub; i++) {
            string[] s = Console.ReadLine().Split(' ');
            for (int j = 0; j < s.Length; j++) {
                if (dic.ContainsKey(s[j])) dic[s[j]]++;
                else dic.Add(s[j], 1);
            }
        }
    }
    static void Main(string[] args) {
        Input();
        var a = new Dictionary<string, int>();
        int MaxTime = 2;
        foreach (var item in dic) {
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
            if (b.Key.CompareTo( item.Key)==1) b = item;
        }
        Console.Write(b.Key + " " + b.Value);
        if (a.Count > 1) Console.WriteLine(" "+a.Count);
        else Console.WriteLine();
    }
}
