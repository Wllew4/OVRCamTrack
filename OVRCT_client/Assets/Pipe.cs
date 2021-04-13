using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.IO;
using System.IO.Pipes;

public class Pipe : MonoBehaviour
{
    private NamedPipeClientStream client = new NamedPipeClientStream("OVRCTPipe");
    StreamReader reader;
    StreamWriter writer;
    // Start is called before the first frame update
    void Start()
    {
        client.Connect();
        reader = new StreamReader(client);
        writer = new StreamWriter(client);
    }

    // Update is called once per frame
    void Update()
    {
        writer.WriteLine("Hello World!");
        writer.Flush();
    }
}
