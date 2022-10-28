using System.Collections;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class PlayerState : MonoBehaviour
{
    public int maxHp = 10;
    public int maxSanity = 100;
    public bool IsInsane { get; private set; }

    private int _hp;
    private int hp
    {
        get => _hp;
        set
        {
            _hp = value;
            healthSlider.value = ((float) _hp) / maxHp;
        }
    }

    private int _sanity;
    private int sanity
    {
        get => _sanity;
        set
        {
            _sanity = value;
            sanitySlider.value = ((float) _sanity) / maxSanity;
        }
    }

    private float sanityRestoreTime = 1f;

    private Slider healthSlider;
    private Slider sanitySlider;
    private float invincibilityTime = 0;

    void Start()
    {
        healthSlider = GameObject.Find("HUD/Health Bar").GetComponent<Slider>();
        sanitySlider = GameObject.Find("HUD/Sanity Bar").GetComponent<Slider>();

        hp = maxHp;
        sanity = maxSanity;
        IsInsane = false;
    }

    void Update()
    {
        invincibilityTime = Mathf.Max(0, invincibilityTime - Time.deltaTime);

        sanityRestoreTime = Mathf.Max(0, sanityRestoreTime - Time.deltaTime);
        if (sanityRestoreTime <= 0)
        {
            ModifySanity(+1);
        }
    }

    void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Enemy" && invincibilityTime <= 0)
        {
            TakeDamage();
        }
    }

    public void TakeDamage()
    {
        hp--;
        ModifySanity(-Random.Range(1, 11));

        if (hp == 0) 
        {
            Die();
        }
        else 
        {
            invincibilityTime = 1f;
            StartCoroutine( Flash() );
        }
    }

    private void Die()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }

    public void OnEnemyKilled()
    {
        ModifySanity(-1);
    }
    private void ModifySanity(int delta)
    {
        sanity = Mathf.Clamp(sanity + delta, 0, maxSanity);
        
        if (!IsInsane && sanity == 0)
        {
            IsInsane = true;
            EnableInsanityEffects();
        }
        else if (IsInsane && sanity >= 25)
        {
            IsInsane = false;
            DisableInsanityEffects();
        }

        sanityRestoreTime = delta < 0 ? 1f : 0.25f;
    }

    private void EnableInsanityEffects()
    {
        foreach (var enemy in GameObject.FindGameObjectsWithTag("Enemy"))
        {
            var state = enemy.GetComponent<EnemyState>();
            state.EnableInsanityEffects();
        }
    }

    private void DisableInsanityEffects()
    {
        foreach (var enemy in GameObject.FindGameObjectsWithTag("Enemy"))
        {
            var state = enemy.GetComponent<EnemyState>();
            state.DisableInsanityEffects();
        }
    }

    IEnumerator Flash()
    {
        for (int i = 0; i < 5; i++)
        {
            GetComponent<Renderer>().enabled = false;
            yield return new WaitForSeconds(0.1f);
            GetComponent<Renderer>().enabled = true;
            yield return new WaitForSeconds(0.1f);
        }
    }
}
