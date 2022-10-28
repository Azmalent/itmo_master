using UnityEngine;

public class Bullet : MonoBehaviour
{
    void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Enemy")
        {
            var playerState = GameObject.FindGameObjectWithTag("Player").GetComponent<PlayerState>();
            playerState.OnEnemyKilled();

            var enemyState = collision.gameObject.GetComponent<EnemyState>();
            enemyState.TakeDamage();
        }

        Destroy(gameObject);
    }
}
