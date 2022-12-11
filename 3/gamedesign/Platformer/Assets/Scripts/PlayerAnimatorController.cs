using System;
using UnityEngine;

public class PlayerAnimatorController : MonoBehaviour
{
    private Animator animator;
    private Vector3 scale;

    public void Start() 
    {
        animator = GetComponent<Animator>();
        scale = transform.localScale;
    }

    private void Flip()
    {
        scale.x *= -1;
        transform.localScale = scale;
    }

    public void UpdateParameters(float motion, bool isGrounded)
    {
        animator.SetFloat("Motion", motion);
        if (motion * scale.x < 0) Flip();

        animator.SetBool("Is Grounded", isGrounded);
    }
}
