import clsx from 'clsx';
import Link from '@docusaurus/Link';
import Heading from '@theme/Heading';
import styles from './index.module.css';
import { ReactTyped } from 'react-typed';

function Title() {
  return (
    <div>
      <Heading as='h1' className={`hero__title ${styles.Title}`}>
        A {" "}
        <ReactTyped
          className={styles.TitleHighlighted}
          strings={[
            '5v5',
            'blazingly fast',
            'character-based',
            'simple',
            'low poly',
            'minimalistic',
            'coherent',
            'DRM-free',
            'competitive'
          ]}
          typeSpeed={100}
          loop
          backSpeed={20}
          cursorChar='|'
          showCursor={true}
        />
        <br/>
        libre tactical shooter
      </Heading>
    </div>
  );
}

function Subtitle() {
  return (
    <p className={`hero__subtitle ${styles.Subtitle}`}>
      🐰 <b>Sparky</b> is created and maintained in loving memory of <b>Sparky</b>, aka <b>Chispitas</b>, aka <b>Chispis</b>, in the hope he will become immortal and, eventually, one with the Force. 🐰
      <br/>
      <i>To the moon and back, forever ❤</i>
    </p>
  );
}

function Button({ isPrimary, txt, path }) {
  return (
    <div className={styles.Button}>
      <Link className={`button button--${isPrimary ? 'primary' : 'secondary' } button--lg`} to={path}>
        {txt}
      </Link>
    </div>
  );
}

function ButtonPair() {
  return (
    <div className={styles.ButtonPair}>
      <Button
        isPrimary
        txt='Get started'
        path='/docs/getting-started/2.1-getting-started'
      />
      <Button
        txt='Learn the basics >'
        path='/docs/overview/1.1-what-is-sparky'
      />
    </div>
  );
}

function Info() {
  return (
    <div className={styles.Info}>
      <Title />
      <Subtitle />
      <ButtonPair />
    </div>
  );
}

function Logo() {
  return (
    <img
      className={styles.Logo}
      src='/img/3d-low-poly-scene.png' />
  );
}

export default function HomepageHeader() {
  return (
    <header className={clsx('hero hero--secondary', styles.heroBanner)}>
      <div className={`container ${styles.Container} fade-in-anim`}>
        <Info />
        <Logo />
      </div>
    </header>
  );
}
