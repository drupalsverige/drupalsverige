<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function drupalse_showcase_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function drupalse_showcase_imagecache_default_presets() {
  $items = array(
    'showcase_small_thumb' => array(
      'presetname' => 'showcase_small_thumb',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '185',
            'height' => '115',
          ),
        ),
      ),
    ),
    'showcase_thumb' => array(
      'presetname' => 'showcase_thumb',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '350',
            'height' => '230',
          ),
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Implementation of hook_node_info().
 */
function drupalse_showcase_node_info() {
  $items = array(
    'showcase' => array(
      'name' => t('Showcase'),
      'module' => 'features',
      'description' => t('En Drupalwebbplats som är värld att lyfta fram på drupalsverige.se. Showcases kan markeras för visning på förstasidan, sorteras som svenska eller utländska/internationella webbplatser, och även länka till leverantörer.'),
      'has_title' => '1',
      'title_label' => t('Sajtnamn'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_rules_defaults().
 */
function drupalse_showcase_rules_defaults() {
  return array(
    'rules' => array(
      'rules_take_care_of_showcase_suggestions' => array(
        '#type' => 'rule',
        '#set' => 'event_node_insert',
        '#label' => 'Take care of showcase suggestions',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'drupalse_showcase',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#type' => 'condition',
            '#settings' => array(
              'roles' => array(
                '0' => 1,
              ),
              'operation' => 'OR',
              '#argument map' => array(
                'user' => 'user',
              ),
            ),
            '#name' => 'rules_condition_user_hasrole',
            '#info' => array(
              'label' => 'Acting user is anonymous',
              'label callback' => FALSE,
              'arguments' => array(
                'user' => array(
                  'type' => 'user',
                  'label' => 'User',
                ),
              ),
              'module' => 'User',
            ),
            '#weight' => 0,
          ),
          '1' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Content is Showcase',
              'label callback' => FALSE,
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#name' => 'rules_condition_content_is_type',
            '#settings' => array(
              'type' => array(
                'showcase' => 'showcase',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#type' => 'condition',
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#type' => 'action',
            '#settings' => array(
              'auto_save' => 1,
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_core_node_unpublish_action',
            '#info' => array(
              'label' => 'Unpublish showcase',
              'label callback' => FALSE,
              'module' => 'Node',
              'arguments' => array(
                'node' => array(
                  'label' => 'Content',
                  'type' => 'node',
                ),
              ),
              'base' => 'rules_core_action_execute',
              'action_name' => 'node_unpublish_action',
              'configurable' => FALSE,
            ),
            '#weight' => 0,
          ),
          '1' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Show a thank-you message',
              'label callback' => FALSE,
              'module' => 'System',
              'eval input' => array(
                '0' => 'message',
              ),
            ),
            '#name' => 'rules_action_drupal_message',
            '#settings' => array(
              'message' => 'Tack för ditt förslag till sajtgalleriet! Administratörerna för drupalsverige.se har meddelats om ditt förslag, och kommer att publicera det inom kort.',
              'error' => 0,
            ),
            '#type' => 'action',
          ),
          '2' => array(
            '#type' => 'action',
            '#settings' => array(
              'path' => 'galleri',
              'query' => '',
              'fragment' => '',
              'force' => 0,
              'immediate' => 0,
            ),
            '#name' => 'rules_action_drupal_goto',
            '#info' => array(
              'label' => 'Redirect to showcase gallery',
              'label callback' => FALSE,
              'module' => 'System',
              'eval input' => array(
                '0' => 'path',
                '1' => 'query',
                '2' => 'fragment',
              ),
            ),
            '#weight' => 0,
          ),
          '3' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Send a mail to an administrator (PLEASE UPDATE WITH NEW ADDRESS)',
              'label callback' => FALSE,
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
              'subject' => 'New Showcase at drupalsverige.se',
              'message' => 'There\'s a new Showcase uploaded at drupalsverige.se!
You can view and publish it at http://drupalsverige.se/node/[node:nid]

Kind regards,
//the robot at drupalsverige.se',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'message' => array(
                    '0' => 'node',
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

/**
 * Implementation of hook_views_api().
 */
function drupalse_showcase_views_api() {
  return array(
    'api' => '2',
  );
}
