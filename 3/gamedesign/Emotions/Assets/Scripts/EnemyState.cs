using UnityEngine;

public class EnemyState : MonoBehaviour
{
    public int hp = 1;

    private PlayerState playerState;
    private SpriteRenderer spriteRenderer;
    private Color trueColor;
    private Color insanityColor;

    void Start()
    {
        playerState = GameObject.FindGameObjectWithTag("Player").GetComponent<PlayerState>();
        spriteRenderer = GetComponent<SpriteRenderer>();

        trueColor = spriteRenderer.color;
        insanityColor = Random.ColorHSV();

        if (playerState.IsInsane)
        {
            EnableInsanityEffects();
        }
    }

    public void TakeDamage()
    {
        hp--;
        if (hp <= 0)
        {
            Destroy(gameObject);
        }
    }

    public void EnableInsanityEffects()
    {
        spriteRenderer.color = insanityColor;
    }

    public void DisableInsanityEffects()
    {
        spriteRenderer.color = trueColor;
    }
}
