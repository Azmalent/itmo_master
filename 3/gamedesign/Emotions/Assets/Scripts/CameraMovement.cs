using UnityEngine;

public class CameraMovement : MonoBehaviour
{
    public Transform target;
    public Vector3 targetOffset;

    void FixedUpdate()
    {
        transform.position = target.position + targetOffset;
    }
}
