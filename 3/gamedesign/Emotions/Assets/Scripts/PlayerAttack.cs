using UnityEngine;

public class PlayerAttack : MonoBehaviour
{
    public GameObject bulletPrefab;
    public Transform firePoint;
    public float bulletForce = 20f;

    private PlayerState playerState;
    private float cooldown = 0;

    private int remainingBullets = -1;

    void Start()
    {
        playerState = GetComponent<PlayerState>();
    }

    void Update()
    {
        cooldown = Mathf.Max(0, cooldown - Time.deltaTime); 

        if(Input.GetButton("Fire1") && cooldown <= 0)
        {
            Shoot();
        }
    }

    void Shoot()
    {
        var direction = firePoint.up;
        if (playerState.IsInsane)
        {
            var angle = Random.Range(-15f, 15f);
            var direction2d = new Vector2(direction.x, direction.y).Rotate(angle);
            direction = new Vector3(direction2d.x, direction2d.y);

            cooldown = Random.Range(0.1f, 0.3f);
        }
        else
        {
            cooldown = 0.2f;
        }

        GameObject bullet = Instantiate(bulletPrefab, firePoint.position, firePoint.rotation);
        var rb = bullet.GetComponent<Rigidbody2D>();
        rb.AddForce(direction * bulletForce, ForceMode2D.Impulse);

        if (playerState.IsInsane)
        {
            remainingBullets--;
        }
    }
}
