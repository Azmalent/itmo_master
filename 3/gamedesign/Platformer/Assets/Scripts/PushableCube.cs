using UnityEngine;

public class PushableCube : MonoBehaviour
{
    public LayerMask PlatformMask;

    private BoxCollider2D boxCollider;

    private void Start() 
    {
        boxCollider = GetComponent<BoxCollider2D>();
    }

    void Update()
    {
        var center = boxCollider.bounds.center;
        var extents = boxCollider.bounds.extents;
        var size = boxCollider.bounds.size;

        var hit = Physics2D.BoxCast(center + Vector3.down * extents.y, new Vector2(size.x, 1f), 0f, Vector2.down, 0.1f, PlatformMask);
        transform.parent = (hit && hit.collider.tag == "Moving Platform") ? hit.collider.transform : null;
    }
}
