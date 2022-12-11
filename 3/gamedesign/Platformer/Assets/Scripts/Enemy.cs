using UnityEngine;
using UnityEngine.SceneManagement;

public class Enemy : MonoBehaviour 
{
	public float Speed = 2.5f;
	public LayerMask GroundMask;

	private Vector3 scale;
	private Rigidbody2D rigidBody;
	private BoxCollider2D boxCollider;

	private float direction = 1;
	private float width;

	private void Start() 
	{
		scale = transform.localScale;
		rigidBody = GetComponent<Rigidbody2D>();
		boxCollider = GetComponent<BoxCollider2D>();

		width = GetComponent<SpriteRenderer>().bounds.extents.x;

		rigidBody.velocity = new Vector2(direction * Speed, rigidBody.velocity.y);
	}
	
	private void FixedUpdate() 
	{
		Vector2 linecastStart = transform.position;
		Vector2 linecastEnd = linecastStart + new Vector2(0.75f * direction, 0);

		bool hasObstacle = Physics2D.Linecast(linecastStart, linecastEnd, GroundMask);
		
		linecastStart = (Vector2) transform.position + new Vector2(boxCollider.bounds.extents.x * direction, 0);
		linecastEnd = linecastStart - new Vector2(0, boxCollider.bounds.extents.y + 0.5f);
		bool hasGround = Physics2D.Linecast(linecastStart, linecastEnd, GroundMask);
		
		if (hasObstacle || !hasGround)
		{
			direction *= -1;
			scale.x *= -1;
			transform.localScale = scale;
		}
		else
		{
			rigidBody.velocity = new Vector2(direction * Speed, rigidBody.velocity.y);
		}

		UnityEngine.Debug.DrawLine(linecastStart, linecastEnd);
	}

	private void OnCollisionEnter2D(Collision2D collision) 
    {
        if (collision.gameObject.tag == "Player")
        {
			SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }
    }
}