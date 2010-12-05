<?php

/**
 * Implementation of hook_rules_defaults().
 */
function drupalsverige_notifications_rules_defaults() {
  return array(
    'rules' => array(
      'rules_drupalsverige_notify' => array(
        '#type' => 'rule',
        '#set' => 'event_user_insert',
        '#label' => 'Notify administrator of user registrations',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'drupalsverige_notify',
          'drupalsverige_notifications' => 'drupalsverige_notifications',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#settings' => array(
              '#argument map' => array(
                'user1' => 'account',
                'user2' => 'user',
              ),
            ),
            '#type' => 'condition',
            '#name' => 'rules_condition_user_comparison',
            '#info' => array(
              'label' => 'Account is created by administator',
              'label callback' => FALSE,
              'arguments' => array(
                'user1' => array(
                  'type' => 'user',
                  'label' => 'User account 1',
                ),
                'user2' => array(
                  'type' => 'user',
                  'label' => 'User account 2',
                ),
              ),
              'module' => 'User',
            ),
            '#weight' => 0,
            '#negate' => 1,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Send a mail to an arbitrary mail address',
              'module' => 'System',
              'eval input' => array(
                '0' => 'subject',
                '1' => 'message',
                '2' => 'from',
                '3' => 'to',
              ),
            ),
            '#name' => 'rules_action_mail',
            '#settings' => array(
              'to' => 'adam@anyro.se',
              'from' => '',
              'subject' => 'New user at drupalsverige.se: [account:user]',
              'message' => 'The new user [account:user] has registered at drupalsverige.se!
You can view the user account at http://drupalsverige.se/user/[account:uid].

All the best,
//the robot at drupalsverige.se',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'subject' => array(
                    '0' => 'account',
                  ),
                  'message' => array(
                    '0' => 'account',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
    ),
  );
}
