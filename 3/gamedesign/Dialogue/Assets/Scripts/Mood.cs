using System.Collections.Generic;
using UnityEngine;

public class Mood : MonoBehaviour
{
    public enum Type
    {
        Neutral, Happy, Sad, Angry
    }

    private static float MOOD_RADIUS = 0.25f;
    
    private static Dictionary<Type, Vector2> MOOD_POINTS = new Dictionary<Type, Vector2> {
        { Type.Happy, new Vector2(0, 1) },
        { Type.Sad, new Vector2(Mathf.Cos(210 * Mathf.Deg2Rad), Mathf.Sin(210 * Mathf.Deg2Rad))},
        { Type.Angry, new Vector2(Mathf.Cos(330 * Mathf.Deg2Rad), Mathf.Sin(330 * Mathf.Deg2Rad))}
    };

    public RectTransform Triangle;
    public RectTransform Circle;

    private Vector2 position;
    public Type MoodType = Type.Neutral;

    public void Change(Type targetMood, float magnitude)
    {
        Debug.Log(magnitude);
        var targetPoint = MOOD_POINTS[targetMood];
        position = Vector2.MoveTowards(position, targetPoint, magnitude);

        float a = Triangle.rect.width;
        float r = a / Mathf.Sqrt(3);
        Circle.localPosition = position * r;

        MoodType = Type.Neutral;
        foreach (var moodPoint in MOOD_POINTS)
        {
            if (Vector2.Distance(position, moodPoint.Value) <= MOOD_RADIUS)
            {
                MoodType = moodPoint.Key;
                break;
            }
        }
    }

    public void ChangeToHappy(int magnitude)
    {
        Change(Type.Happy, magnitude / 100f);
    }

    public void ChangeToSad(int magnitude)
    {
        Change(Type.Sad, magnitude / 100f);
    }

    public void ChangeToAngry(int magnitude)
    {
        Change(Type.Angry, magnitude / 100f);
    }

    public void Reset() 
    {
        position = Vector2.zero;
        MoodType = Type.Neutral;
        Circle.transform.localPosition = Vector2.zero;
    }

    public string GetMoodSuffix()
    {
        switch(MoodType)
        {
            case Type.Happy:
                return " (радостный)";

            case Type.Sad:
                return " (грустный)";

            case Type.Angry:
                return " (злой)";

            default:
                return "";
        }
    }
}
