using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DoSomething : MonoBehaviour
{
    //先ほど作成したクラス
    public SerialHandler serialHandler;
    //デバッグ用
    private float signal;
    private Vector3 m_pos;


    void Start()
    {
        //信号を受信したときに、そのメッセージの処理を行う
        serialHandler.OnDataReceived += OnDataReceived;
        //デバッグ用
        m_pos = transform.localScale;
    }

    void Update()
    {
        //文字列を送信
        serialHandler.Write("Received!");
        // 位置を更新
        transform.localScale = m_pos;
        m_pos.x = signal/1000 + 1;
        m_pos.y = signal/1000 + 1;
        m_pos.z = signal/1000 + 1;
    }

    //受信した信号(message)に対する処理
    void OnDataReceived(string message)
    {
        var data = message.Split(
                new string[] { "\t" }, System.StringSplitOptions.None);
        //Debug.Log(data[0]);
        Debug.Log(message);
        signal = float.Parse(message);


        if (data.Length < 2) return;

        try
        {
           
        }
        catch (System.Exception e)
        {
            Debug.LogWarning(e.Message);
        }
    }
}