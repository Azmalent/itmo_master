using UnityEngine;

public class EnemyMovement : MonoBehaviour
{
    public float movementSpeed = 5f;

    private Rigidbody2D rb;
    private Transform playerPos;

    void Start()
    {
        rb = GetComponent<Rigidbody2D>();
        playerPos = GameObject.FindGameObjectWithTag("Player").transform;
    }

    void Update()
    {
        transform.position = Vector2.MoveTowards(transform.position, playerPos.position, movementSpeed * Time.deltaTime);
        
        var lookDirection =  transform.position - playerPos.position;
        float angle = Mathf.Atan2(lookDirection.y, lookDirection.x) * Mathf.Rad2Deg + 90.0f;
        rb.rotation = angle;
    }
}
