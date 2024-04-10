import clsx from 'clsx';
import Heading from '@theme/Heading';
import styles from './styles.module.css';

const imgRootPath = '/sparky/img';

const featureList = [
  {
    title: 'Free/Libre',
    image: `${imgRootPath}/feature-free-libre.png`,
    description: (
      <>
        As in <b>free speech</b> and as in <b>free bear</b>: You have the
        <a href='https://www.gnu.org/philosophy/free-sw.html'> freedom </a>
        to run, copy, distribute, study, change and improve the software.
      </>
    )
  },
  {
    title: 'Fast. Blazingly fast',
    image: `${imgRootPath}/feature-blazingly-fast.png`,
    description: (
      <>
        Made in <b>pure C</b>, not only the code is simple and easy to understand,
        but it offers an <b>efficiency</b> and <b>performance</b> that is off the charts.
      </>
    )
  },
  {
    title: 'Low Poly',
    image: `${imgRootPath}/feature-low-poly.png`,
    description: (
      <>
        Meshes with thousands of polygons? Why? For it to require you a +$1000 GPU?
        Let's keep it <b>minimalist</b> without sacrificing on its <b>looks</b>. 
      </>
    )
  },
  {
    title: 'Hero FPS',
    image: `${imgRootPath}/feature-hero-fps.png`,
    description: (
      <>
        Characters with distinctive and fun <b>abilities</b> and <b>weapons</b> that adapt to each
        gaming style. All of that while being <b>first-person</b> and <b>slow-paced</b>.
      </>
    )
  },
  {
    title: 'Customizable',
    image: `${imgRootPath}/feature-customizable.png`,
    description: (
      <>
        Both the <b>codebase</b> and all <b>tools</b> built around it offer the <b>flexibility</b> for
        extensive customization according to <b>your needs</b>.
      </>
    )
  },
  {
    title: 'Decentralised',
    image: `${imgRootPath}/feature-decentralised.png`,
    description: (
      <>
        Create <b>your own server</b> wherever and however you want, let users <b>choose</b> which one to
        join. <b>Own</b> your software, don't be a puppet.
      </>
    )
  },
];

function Feature({title, image, description}) {
  return (
    <div className={clsx('col col--4')}>
      <div className='text--center'>
        <img className={styles.featureImg} src={image} alt={title} />
      </div>
      <div className='text--center padding-horiz--md'>
        <Heading as='h3'>{title}</Heading>
        <p>{description}</p>
      </div>
    </div>
  );
}

export default function HomepageFeatures() {
  return (
    <section className={styles.features}>
      <div className='container'>
        <div className='row'>
          {featureList.map((props, idx) => (
            <Feature key={idx} {... props} />
          ))}
        </div>
      </div>
    </section>
  );
}
