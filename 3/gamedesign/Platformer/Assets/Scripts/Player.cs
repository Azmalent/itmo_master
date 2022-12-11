using System;
using System.Collections;
using UnityEngine;
using UnityEngine.UI;

public class Player : MonoBehaviour
{
    private const float FALL_GRAVITY_FACTOR = 1.5f;
    private const float LOW_JUMP_GRAVITY_FACTOR = 1f;

    public float Speed = 5f;
    public float JumpVelocity = 8f;
    public int MaxEnergy = 5;

    public LayerMask GroundMask;
    public LayerMask SlopeMask;
    public LayerMask PlatformMask;
    public PhysicsMaterial2D HighFrictionMaterial;
    public PhysicsMaterial2D ZeroFrictionMaterial;

    private float motion = 0f;
    private bool isGrounded = false;
    private Collider2D platformCollider;
    private int remainingEnergy;


    private BoxCollider2D boxCollider;
    private Rigidbody2D rigidBody;
    private PlayerAnimatorController animatorController;
    private Text energyCounter;

    void Start()
    {
        boxCollider = GetComponent<BoxCollider2D>();
        rigidBody = GetComponent<Rigidbody2D>();
        animatorController = GetComponent<PlayerAnimatorController>();
        energyCounter = GameObject.Find("HUD/Energy Counter").GetComponent<Text>();

        SetEnergy(MaxEnergy);
    }

    void Update()
    {
        var center = boxCollider.bounds.center;
        var extents = boxCollider.bounds.extents;
        var size = boxCollider.bounds.size;

        var hit = Physics2D.BoxCast(center + Vector3.down * extents.y, new Vector2(size.x, 1f), 0f, Vector2.down, 0.1f, GroundMask);
        transform.parent = (hit && hit.collider.tag == "Moving Platform") ? hit.collider.transform : null;

        isGrounded = hit;
        
        bool isOnSlope = isGrounded && Physics2D.Raycast(center, Vector2.down, 1.5f, SlopeMask);
        rigidBody.sharedMaterial = (motion == 0 && isOnSlope) ? HighFrictionMaterial : ZeroFrictionMaterial;

        var platformHit = Physics2D.Raycast(center, Vector2.down, 1.5f, PlatformMask);
        platformCollider = platformHit ? platformHit.collider : null;

        animatorController.UpdateParameters(motion, isGrounded);
    }

    void FixedUpdate()
    {
        bool jumpHeld = Input.GetKey(KeyCode.Space) || Input.GetKey(KeyCode.UpArrow) || Input.GetKey(KeyCode.W);

        rigidBody.velocity = new Vector2(motion, rigidBody.velocity.y);
        if (rigidBody.velocity.y < 0)
        {
            var additionalGravity = Vector2.up * Physics.gravity.y * FALL_GRAVITY_FACTOR;
            rigidBody.velocity += additionalGravity * Time.deltaTime;
        }
        else if (rigidBody.velocity.y > 0 && !jumpHeld)
        {
            var additionalGravity = Vector2.up * Physics.gravity.y * LOW_JUMP_GRAVITY_FACTOR;
            rigidBody.velocity += additionalGravity * Time.deltaTime;
        }
    }

    public void SetEnergy(int value)
    {
        remainingEnergy = value;
        energyCounter.text = "Energy: " + remainingEnergy + "/" + MaxEnergy;
    }

    public void SetMovingDirection(int direction)
    {
        motion = Speed * direction;
    }

    public void Jump()
    {
        if (isGrounded && remainingEnergy > 0)
        {
            SetEnergy(remainingEnergy - 1);

            var v = rigidBody.velocity;
            rigidBody.velocity = new Vector2(v.x, JumpVelocity);

            transform.SetParent(null);
        }
    }

    public void DropDown()
    {
        if (platformCollider != null)
        {
            StartCoroutine( DisablePlatformCollision() );
        }
    }

    private IEnumerator DisablePlatformCollision()
    {
        var platformCollider = this.platformCollider;
        Physics2D.IgnoreCollision(boxCollider, platformCollider, true);
        yield return new WaitForSeconds(0.5f);
        Physics2D.IgnoreCollision(boxCollider, platformCollider, false);
    }
}
