using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovingPlatform : MonoBehaviour
{
    public float Speed = 1f;
    public Transform[] Points;
    public float PauseDuration = 1f;

    private int currentPoint = 0;
    private float remainingPauseDuration = 0;

    private void Start() 
    {
        remainingPauseDuration = PauseDuration;    
    }

    void Update()
    {
        if (remainingPauseDuration > 0)
        {
            remainingPauseDuration -= Time.deltaTime;
        }
        else
        {
            if (Points.Length == 0) return;

            var destination = Points[currentPoint];
            transform.position = Vector3.MoveTowards(transform.position, destination.position, Speed * Time.deltaTime);

            var distance = Vector3.Distance(transform.position, destination.position);
            if (distance < double.Epsilon)
            {
                currentPoint = (currentPoint + 1) % Points.Length;
                remainingPauseDuration = PauseDuration;
            }
        }
    }
}
